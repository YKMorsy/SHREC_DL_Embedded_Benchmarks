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

from edgetpu.basic.basic_engine import BasicEngine

class MobileNet:

	def __init__(self, tfLiteFilename):
		self.basic_engine = BasicEngine(tfLiteFilename)
		
	def predict(self, images, max=5):
		raw = self.basic_engine.run_inference(images)
		predictions = raw[1]
		results = {'predictions': []}
		for i in range(len(predictions)):
			ordered = (-predictions).argsort()
			topn=[]
			for j in ordered[:max]:
				# convert numpy.int64 to int for JSON serialization later
				topn.append(int(j - 1))
			results['predictions'].append(topn)
			return results

