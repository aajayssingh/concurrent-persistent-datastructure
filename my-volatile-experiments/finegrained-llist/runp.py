import os
import time
for x in range(50):
    print('run --'.format(x))
    os.system("./fine-list")
    time.sleep(1)
