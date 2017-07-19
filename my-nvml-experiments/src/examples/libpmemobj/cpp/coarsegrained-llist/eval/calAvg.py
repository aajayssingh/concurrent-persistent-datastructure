path = './'
pathop = './'

outp = open(pathop + 'avg', 'a')
for i in range(1,6):
	num = 0
	with open(path + format(i*10), 'r') as inp:
	   for line in inp:
		   try:
			   num += float(line)
		   except ValueError:
			   print('{} is not a number!'.format(line))
	print('dir {}  '.format(i*10))
	print('avg num {}  '.format(num/50))
	outp.write(format(num/50)+'\n')
outp.close()
