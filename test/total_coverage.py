import os
import subprocess
import re
print(123)
# 指定覆盖率文件的目录
coverage_directory = "./"

coverage_files = [os.path.join(coverage_directory, f) for f in os.listdir(
    coverage_directory) if re.match(r".+\.cov$", f)]
print(coverage_files)



open_cpp_coverage_command = ["OpenCppCoverage.exe"]
for coverage_file in coverage_files:
    open_cpp_coverage_command.extend(["--input_coverage", coverage_file])
open_cpp_coverage_command.extend(
    ["--export_type=html:total_coverage.html"])

subprocess.call(open_cpp_coverage_command)
