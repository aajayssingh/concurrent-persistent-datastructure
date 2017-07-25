import os
import time
for x in range(50):
    print('run --'.format(x))
    os.system("./coarse-plist ajplist")
    time.sleep(1)
