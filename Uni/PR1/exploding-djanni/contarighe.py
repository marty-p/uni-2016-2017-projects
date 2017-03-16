import glob

lfiles = glob.glob('*.c')
lfiles += glob.glob('*.h')

cnt1 = 0
cnt2 = 0
for fn in lfiles:
	with open(fn) as f:
		cnt1 += len(f.read().split("\n"))
		f.seek(0)
		cnt2 += sum(1 for line in f if line.strip() and not line.startswith('//') and not line.startswith('/*') and not line.startswith('*/'))
print "Tutto: %d, Niente spazi/commenti: %d" % (cnt1, cnt2)
