import subprocess
import sys
import time

outpath = "AOThing.output.txt"
outfile = open(outpath, "w")
sys.stdout = outfile # set this output to outfile 

def runTest(uaiFile, numSamples):
  for i in range(10):
    # run the homework jar with the given parameters, redirect output to outfile as well
    subprocess.call(["java", "-Xmx1500M", "-jar", "aosampling.jar", uaiFile, numSamples], stdout=outfile, stderr=outfile, shell=False)
    outfile.flush()
  
def main():
  uaiPath = "H:/Downloads/"
  files = ["uai08_test1"]
  #s = ["100", 
    #"1000", 
    #"10000", 
    #"100000"]
  s = ["1000000"]

  for sval in s:
    for filename in files:
      uaifilePath = uaiPath + filename + ".uai"
      
      print(uaifilePath, sval)
      outfile.flush()
      runTest(uaifilePath, sval)
          
# Execution begins here
if __name__ == "__main__":
  #start = time.time()
  main()
  #end = time.time()
  #print("Testing completed in", end - start, "s.")
  
outfile.close()