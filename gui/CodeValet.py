import csv
import cog
import urllib.request
import time
import os
# Code Valet
# Automatically generate code for mundane things

class CodeValet:
	def __init__ (self):
		# Check if the latest version of spec csvs have been downloaded yet.
		# Assuming that download one file and cog writing will not take more than 6 seconds to complete
		# If the file is modified more than 6 seconds ago, download again
		
		if int(time.time()) - os.path.getmtime('message_spec.ignore.csv') > 6:
			url = "https://docs.google.com/spreadsheets/d/12pyWhpnUc2WIkpixExfhn6BQ4HnPdwTVp-OGuGELdZY/pub?gid=1325505480&single=true&output=csv"
			urllib.request.urlretrieve(url, "message_spec.ignore.csv")
			print("\nmessage_spec downloaded")
			
		if int(time.time()) - os.path.getmtime('enum_spec.ignore.csv') > 6:
			url = "https://docs.google.com/spreadsheets/d/1cqJtXhl5wbPdjxEVehXyv79kurtfGodk5sUIdn8WmFg/pub?gid=1924614231&single=true&output=csv"
			urllib.request.urlretrieve(url, "enum_spec.ignore.csv")
			print("\nenum_spec downloaded")

		self.message_spec = csv.DictReader(open("message_spec.ignore.csv")) 
		self.enum_spec = csv.DictReader(open("enum_spec.ignore.csv")) 

	# For afm.h
	def afm_h_define(self):
		file_name = "afm.h"
		cog.outl("/* Automatically Generated Code - Editing is futile! */")
		for row in self.message_spec:
			if len(row['Serial Port Message']) > 0:
				cog.outl("#define "+row['Serial Port Message']+"  0x"+row['Msg ID (0x)'])
				cog.outl("#define "+row['Serial Port Message']+"_RSPLEN    "+row['Reply msg length'])
		for row in self.enum_spec:
			if len(row['Variable Name']) > 0 and file_name in row['CVFile']:
				cog.outl("#define "+row['Variable Name']+"  "+row['Variable Value'])
				
	# For afm_data.h
	def afm_data_h_define(self):
		file_name = "afm_data.h"
		cog.outl("/* Automatically Generated Code - Editing is futile! */")
		for row in self.enum_spec:
			if len(row['Variable Name']) > 0 and file_name in row['CVFile']:
				cog.outl("#define "+row['Variable Name']+"  "+row['Variable Value'])
		
	
	def msg_rsplen_define(self):
		for row in self.message_spec:
			if len(row['Serial Port Message']) > 0:
				cog.outl("#define "+row['Serial Port Message']+"_RSPLEN    "+row['Reply msg length'])

	def receive_worker_switch(self):
		for row in self.message_spec:
			if len(row['Serial Port Message']) > 0 and len(row['CodeValet_receive_worker_Type']) > 0:
				if int(row['CodeValet_receive_worker_Type']) < 3:
					cog.outl("case " + row['Serial Port Message'] + ":   //CodeValet autogen")
					cog.outl("if ((unsigned char)uart_resp.at(1) != %s) {" % row['Serial Port Message'])
					cog.outl("handle_error(ERR_MSG_ID_MISMATCH);")
					cog.outl("return_queue.push(new returnBuffer(%s, AFM_FAIL));" % row['CodeValet_receive_worker_returnType'])
					cog.outl("break;}")
					cog.outl("if (uart_resp.size() < %s) {" % str(row['Serial Port Message']+"_RSPLEN"))
					cog.outl("handle_error(ERR_MSG_SIZE_MISMATCH);")
					cog.outl("return_queue.push(new returnBuffer(%s, AFM_FAIL));" % row['CodeValet_receive_worker_returnType'])
					cog.outl("break;}")
					if int(row['CodeValet_receive_worker_Type']) == 1:
						cog.outl("return_queue.push(new returnBuffer(%s, AFM_SUCCESS));" % row['CodeValet_receive_worker_returnType'])
					elif int(row['CodeValet_receive_worker_Type']) == 2: 
						cog.outl("if (uart_resp.at(2) == 'o') {")
						cog.outl("return_queue.push(new returnBuffer(%s, AFM_SUCCESS));" % row['CodeValet_receive_worker_returnType'])
						cog.outl("}else{handle_error(ERR_COMMAND_FAILED);")
						cog.outl("return_queue.push(new returnBuffer(%s, AFM_FAIL));}" % row['CodeValet_receive_worker_returnType'])
					cog.outl("break;")
			
				