# 
# Copyright (C) 2019 EEMBC(R). All Rights Reserved
# 
# All EEMBC Benchmark Software are products of EEMBC and are provided under the
# terms of the EEMBC Benchmark License Agreements. The EEMBC Benchmark Software
# are proprietary intellectual properties of EEMBC and its Members and is
# protected under all applicable laws, including all applicable copyright laws.  
# 
# If you received this EEMBC Benchmark Software without having a currently
# effective EEMBC Benchmark License Agreement, you must discontinue use.
# 

import tensorflow as tf
import numpy as np
import time

class MobileNet:

	def __init__(self, frozenGraphFilename, device='cpu'):
		self.frozenGraphFilename = frozenGraphFilename
		self.graph = None
		self.session = None
		self.input_tensor = None
		self.output_tensor = None
		self.__load_graph(device)
		self.__init_predictor()

	def __load_graph(self, device):
		with tf.io.gfile.GFile(self.frozenGraphFilename, "rb") as f:
			graph_def = tf.compat.v1.GraphDef()
			graph_def.ParseFromString(f.read())
		with tf.Graph().as_default() as graph:
			# force prefix to "" using name=
			tf.import_graph_def(graph_def, name="")
		self.graph = graph
		if device == 'cpu':
			config = tf.compat.v1.ConfigProto(device_count={'GPU': 0})
			self.session = tf.compat.v1.Session(config=config, graph=self.graph)
		else:
			self.session = tf.compat.v1.Session(graph=self.graph)

	def __init_predictor(self):
		self.input_tensor = self.graph.get_tensor_by_name('input:0')
		self.output_tensor = self.graph.get_tensor_by_name('MobilenetV1/Predictions/Reshape_1:0')

	def predict(self, images, max=5):
		with self.graph.as_default():
			predictions = self.session.run(
				self.output_tensor, {
					self.input_tensor: images
				})
			results = {
				'predictions': []
			}
			for i in range(len(predictions)):
				ordered = predictions[i].argsort()[-len(predictions[i]):][::-1]
				topn = []
				for j in ordered[:max]:
					# convert numpy.int64 to int for JSON serialization later
					topn.append(int(j - 1))
				results['predictions'].append(topn)
			return results
