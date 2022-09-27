import os
import sys
import subprocess
import time
from prettytable import PrettyTable

build_dir = "build"

verbose = False
simulate = False
for a in sys.argv[1:]:
    if a == "-v":
        verbose = True
    elif a == "-s":
        simulate = True

def run_cmd(cmd):
    if simulate:
        print(cmd)
        return None
    else:
        try:
            if verbose:
                out = subprocess.run(cmd, shell=True, check=True)
            else:
                out = subprocess.run(cmd, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, shell=True, check=True)
        except:
            print("The following command raised an exception:")
            print("  " + cmd)
            exit()
        else:
            if out.returncode != 0:
                print("The following command returned error code " + str(out.returncode))
                print("  " + cmd)
                exit()


print("[BENCHMARKING CUSTOM LZ4 SDL SURFACE FORMAT COMPARED TO PNG/BMP")

run_cmd("rm -rf benchmark_files")
run_cmd("mkdir -p benchmark_files/bmp")
run_cmd("mkdir -p benchmark_files/png")
run_cmd("mkdir -p benchmark_files/png_quant")
run_cmd("mkdir -p benchmark_files/lz4")
run_cmd("mkdir -p benchmark_files/lz4hc")

if len(sys.argv) == 1:
    print("Usage: " + sys.argv[0] + " [file1.png] [file2.bmp] (...)")
    exit()

print("\n## Converting images to formats")

nb_images = 0
for a in sys.argv[1:]:
    if a == "-v" or a == "-s":
        continue
    if not a.endswith("png") and not a.endswith("bmp"):
        continue
    nb_images += 1
    id = a.replace('/','_').split('.')[0]
    run_cmd("./" + build_dir + "/convert " + a + " benchmark_files/bmp/" + id + ".bmp")
    run_cmd("./" + build_dir + "/convert " + a + " benchmark_files/png/" + id + ".png")
    run_cmd("cp benchmark_files/png/" + id + ".png benchmark_files/png_quant/" + id + ".png")
    run_cmd("pngquant -Q 0-50 --ext .png --force benchmark_files/png_quant/" + id + ".png")
    run_cmd("./" + build_dir + "/convert " + a + " benchmark_files/lz4/" + id + ".sdl_surface.lz4")
    run_cmd("./" + build_dir + "/convert " + a + " benchmark_files/lz4hc/" + id + ".sdl_surface.lz4 -hc")

print(" -> " + str(nb_images) + " images used for benchmarking")

print("\n## Running benchmark")
table = PrettyTable()
table.field_names = [ "FORMAT", "READING TIME (s)", "CREATING SURFACE (s)", "CREATING TEXTURE (s)", "TOTAL (s)", "SIZE (MB)" ]

format_name = { "bmp": "BMP", "png": "PNG", "png_quant": "PNG (quant)", "lz4": "LZ4", "lz4hc": "LZ4HC" }

for folder in ["bmp", "png", "png_quant", "lz4", "lz4hc"]:

    size = 0
    for f in os.listdir("benchmark_files/" + folder + "/"):
        size += os.path.getsize("benchmark_files/" + folder + "/" + f)

    out = subprocess.run("./" + build_dir + "/profile benchmark_files/" + folder + "/*",
                         shell=True, check=True, stdout=subprocess.PIPE).stdout.decode()[:-1].split(" ")
    out = [ float(o) for o in out ]

    row = [ format_name[folder] ] + [ str(round(o, 2)) for o in out ] + [ str(round(out[0] + out[1] + out[2], 2)) ] + [ size // (1024 * 1024) ]
    table.add_row (row)

print(table)
