import csv
import cog

# Code Valet
# Automatically generate code for mundane things


	
class CodeValet:
	def __init__ (self):
		self.input_file = csv.DictReader(open("message_spec.csv")) 
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

				
			
				