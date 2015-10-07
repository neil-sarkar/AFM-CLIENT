import csv
import cog

# Code Valet
# Automatically generate code for mundane things


	
class CodeValet:
	def __init__ (self):
		self.input_file = csv.DictReader(open("Serial Message Specifications - Rickey Proposal - Messages.csv")) 
		# print("CSV is open")
	# for row in input_file:
		# if len(row['Serial Port Message']) > 0:
			# print(row['Serial Port Message'],"0x"+row['Msg ID (0x)'])


	def msg_id_define(self):
		cog.outl("/* Automatically Generated Code - Editing is futile! */")
		for row in self.input_file:
			if len(row['Serial Port Message']) > 0:
				cog.outl("#define "+row['Serial Port Message']+"  0x"+row['Msg ID (0x)'])
				cog.outl("#define "+row['Serial Port Message']+"_RSPLEN    "+row['Reply msg length'])
	
	def msg_rsplen_define(self):
		for row in self.input_file:
			if len(row['Serial Port Message']) > 0:
				cog.outl("#define "+row['Serial Port Message']+"_RSPLEN    "+row['Reply msg length'])

	def receive_worker_switch(self):
		for row in self.input_file:
			if len(row['Serial Port Message']) > 0 and len(row['CodeValet_receive_worker_Type']) > 0:
				if int(row['CodeValet_receive_worker_Type']) < 3:
					cog.outl("case " + row['Serial Port Message'] + ":   //CodeValet autogen")
					cog.outl("if (uart_resp.at(1) != %s) {" % row['Serial Port Message'])
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
			
				