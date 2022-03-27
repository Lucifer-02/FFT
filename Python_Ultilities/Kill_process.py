import subprocess
import msvcrt

s = subprocess.check_output('tasklist', shell=False)
if b"CPPTest_FFT.exe" in s:
    print('this process exist')
    subprocess.call(['taskkill', '/F', '/IM', 'CPPTest_FFT.exe'])
else:
    print('this process is not exist')

msvcrt.getch()
