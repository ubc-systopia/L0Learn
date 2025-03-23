#!/usr/bin/env python3
import os
import sys
import subprocess
import glob
import shutil
import zipfile
import tempfile

def run_command(cmd):
    print(f"Running: {' '.join(cmd)}")
    subprocess.check_call(cmd)

def fix_wheel(wheel_path, output_dir):
    print(f"Fixing wheel: {wheel_path}")
    
    # Create a temporary directory to extract the wheel
    with tempfile.TemporaryDirectory() as temp_dir:
        # Extract the wheel
        with zipfile.ZipFile(wheel_path, 'r') as zip_ref:
            zip_ref.extractall(temp_dir)
        
        # Find the extension module
        extension_files = glob.glob(f"{temp_dir}/fastsparsegams/*.so")
        if not extension_files:
            print("No extension module found in the wheel")
            return
        
        extension_file = extension_files[0]
        print(f"Found extension module: {extension_file}")
        
        # Check the dependencies
        otool_output = subprocess.check_output(['otool', '-L', extension_file]).decode('utf-8')
        print(f"Dependencies before fixing:\n{otool_output}")
        
        # Find the Armadillo library
        armadillo_lib = None
        for line in otool_output.splitlines():
            if 'libarmadillo' in line:
                armadillo_lib = line.split()[0].strip()
                break
        
        if not armadillo_lib:
            print("No Armadillo library dependency found")
            return
        
        print(f"Armadillo library dependency: {armadillo_lib}")
        
        # Find the actual Armadillo library on the system
        system_armadillo_lib = None
        for lib_dir in ['/usr/local/lib', '/usr/local/lib64']:
            lib_path = os.path.join(lib_dir, 'libarmadillo.dylib')
            if os.path.exists(lib_path):
                system_armadillo_lib = lib_path
                break
        
        if not system_armadillo_lib:
            print("Could not find Armadillo library on the system")
            return
        
        print(f"Found system Armadillo library: {system_armadillo_lib}")
        
        # Create a lib directory in the wheel
        lib_dir = os.path.join(temp_dir, 'fastsparsegams', 'lib')
        os.makedirs(lib_dir, exist_ok=True)
        
        # Copy the Armadillo library to the wheel
        wheel_armadillo_lib = os.path.join(lib_dir, 'libarmadillo.dylib')
        shutil.copy2(system_armadillo_lib, wheel_armadillo_lib)
        print(f"Copied Armadillo library to: {wheel_armadillo_lib}")
        
        # Fix the install name in the copied library
        run_command(['install_name_tool', '-id', '@loader_path/lib/libarmadillo.dylib', wheel_armadillo_lib])
        
        # Fix the reference in the extension module
        run_command(['install_name_tool', '-change', armadillo_lib, '@loader_path/lib/libarmadillo.dylib', extension_file])
        
        # Check the dependencies again
        otool_output = subprocess.check_output(['otool', '-L', extension_file]).decode('utf-8')
        print(f"Dependencies after fixing:\n{otool_output}")
        
        # Create the output directory if it doesn't exist
        os.makedirs(output_dir, exist_ok=True)
        
        # Create a new wheel with the fixed files
        wheel_name = os.path.basename(wheel_path)
        output_wheel = os.path.join(output_dir, wheel_name)
        
        # Change to the temp directory to create the zip file
        cwd = os.getcwd()
        os.chdir(temp_dir)
        
        # Create a new zip file
        with zipfile.ZipFile(output_wheel, 'w', zipfile.ZIP_DEFLATED) as zip_ref:
            for root, dirs, files in os.walk('.'):
                for file in files:
                    file_path = os.path.join(root, file)
                    arcname = file_path
                    zip_ref.write(file_path, arcname)
        
        # Change back to the original directory
        os.chdir(cwd)
        
        print(f"Created fixed wheel: {output_wheel}")
        return output_wheel

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print(f"Usage: {sys.argv[0]} wheel_path output_dir")
        sys.exit(1)
    
    wheel_path = sys.argv[1]
    output_dir = sys.argv[2]
    
    fix_wheel(wheel_path, output_dir)
