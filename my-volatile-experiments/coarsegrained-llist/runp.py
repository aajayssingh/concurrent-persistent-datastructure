import os
import time
for x in range(50):
    print('run --'.format(x))
    os.system("./coarse-list")
    time.sleep(1)
