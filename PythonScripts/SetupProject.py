#!/usr/bin/env python3.1
print('Copyright Avnish Kirnalli 2022. Made for DrEngine.')

import os
import shutil
import subprocess
from io import BytesIO

# Module checks with Install option
def yes_or_no(question):
    reply = str(input(question + ' (y/n): ')).lower().strip()
    if reply[0] == 'y':
        return True
    if reply[0] == 'n':
        return False

def InstallModule(package):
    if yes_or_no(f'Package {package} not found. Do you want to install Python Package {package}?'):
        subprocess.call(['pip', 'install', package])
        os.system('cls')
        os.system(f'python {os.getcwd()}/PythonScripts/SetupProject.py')
        exit()
    else:
        exit()

try:
    import requests
except ImportError as e:
    InstallModule('requests')
try:
    import zipfile
except ImportError as e:
    InstallModule('zipfile')
try:
    from tqdm import tqdm
except ImportError as e:
    InstallModule('tqdm')

os.chdir(f'{os.getcwd()}/PythonScripts')

def DownloadSDL():
    # Get all releases and find the latest SDL2 version (not SDL3)
    response = requests.get("https://api.github.com/repos/libsdl-org/SDL/releases")
    releases = response.json()
    
    # Find the latest SDL2 release (version starting with "2.")
    versionNo = None
    for release in releases:
        version = release["name"]
        if version.startswith("2."):
            versionNo = version
            break
    
    if versionNo is None:
        print("Error: Could not find any SDL2 releases")
        exit()

    if os.path.exists(f'{os.getcwd()}/../DrEngine/vendor/SDL2'):
        f = open(f'{os.getcwd()}/../DrEngine/vendor/SDL2/version.txt')
        if f.read() == versionNo:
            print('SDL2 Up-to date')
            return
        else:
            print('!!!!!!!!!!SDL2 Outdated. Delete DrEngine/Vendor folder then relaunch the script!!!!!!!!!!!!!!!!!!!')
            print(f'"{os.getcwd()}/../DrEngine/vendor"')
            exit()

    print('Downloading SDL2')

    print(f"SDL2 Version: {versionNo}")

    url = f'https://github.com/libsdl-org/SDL/releases/download/release-{versionNo}/SDL2-devel-{versionNo}-VC.zip'
    req = requests.get(url)

    # Check if the request was successful
    if req.status_code != 200:
        print(f'Error downloading SDL2: HTTP {req.status_code}')
        print(f'Response content: {req.text[:500]}')
        exit()

    # Check if we actually got a ZIP file
    if not req.content.startswith(b'PK'):
        print('Error: Downloaded content is not a ZIP file')
        print(f'Content type: {req.headers.get("content-type", "unknown")}')
        print(f'Content length: {len(req.content)}')
        print(f'First 100 bytes: {req.content[:100]}')
        exit()

    filename = url.split('/')[-1]

    with open(filename, 'wb') as output_file:
        output_file.write(req.content)

    print('Downloaded SDL2.')

    print('Starting SDL2 Extraction')

    with zipfile.ZipFile(BytesIO(req.content)) as zf:
        for member in tqdm(zf.infolist(), desc='Extracting SDL2 '):
            try:
                zf.extract(member, os.getcwd())
            except zipfile.error as e:
                print(f'Error while extracting SDL2: {e}')
                pass

    print('SDL2 extracted Successfully')

    print('Deleting SDL2 Residual Files')

    os.remove(f'{os.getcwd()}/{filename}')

    print('Finalizing SDL2 Setup')

    os.rename(f'SDL2-{versionNo}', 'SDL2')

    # writing version.txt
    with open('SDL2/version.txt', "w") as f:
        f.write(versionNo)

    shutil.move(f'{os.getcwd()}/SDL2', f'{os.getcwd()}/../DrEngine/vendor/SDL2')

    print('SDL2 installed Successfully!')

def DownloadSPDLOG():
    response = requests.get("https://api.github.com/repos/gabime/spdlog/releases/latest")
    versionNo = response.json()["name"]
    versionNo = versionNo.replace('Version ', ' ').strip()

    if os.path.exists(f'{os.getcwd()}/../DrEngine/vendor/spdlog'):
        f = open(f'{os.getcwd()}/../DrEngine/vendor/spdlog/version.txt')
        if f.read() == versionNo:
            print('SPDLOG Up-to date')
            return
        else:
            print('!!!!!!!!!!SPDLOG Outdated. Delete DrEngine/Vendor folder then relaunch the script!!!!!!!!!!!!!!!!!!!')
            print(f'"{os.getcwd()}/../DrEngine/vendor"')
            exit()

    print('Downloading SPDLOG.')

    print(f"SPDLOG Version: {versionNo}")

    url = f'https://github.com/gabime/spdlog/archive/refs/tags/v{versionNo}.zip'
    req = requests.get(url)

    # Check if the request was successful
    if req.status_code != 200:
        print(f'Error downloading SPDLOG: HTTP {req.status_code}')
        print(f'Response content: {req.text[:500]}')
        exit()

    # Check if we actually got a ZIP file
    if not req.content.startswith(b'PK'):
        print('Error: Downloaded SPDLOG content is not a ZIP file')
        print(f'Content type: {req.headers.get("content-type", "unknown")}')
        print(f'Content length: {len(req.content)}')
        print(f'First 100 bytes: {req.content[:100]}')
        exit()

    filename = url.split('/')[-1]

    with open(filename, 'wb') as output_file:
        output_file.write(req.content)

    print('Downloaded SPDLOG.')

    print('Starting SPDLOG Extraction')

    with zipfile.ZipFile(BytesIO(req.content)) as zf:
        for member in tqdm(zf.infolist(), desc='Extracting SPDLOG '):
            try:
                zf.extract(member, os.getcwd())
            except zipfile.error as e:
                print(f'Error while extracting SPDLOG: {e}')
                pass

    print('SPDLOG extracted Successfully')

    print('Deleting SPDLOG Residual Files')

    os.remove(f'{os.getcwd()}/{filename}')

    print('Finalizing SPDLOG Setup')

    os.rename(f'spdlog-{versionNo}', 'spdlog')

    # writing version.txt
    with open('spdlog/version.txt', "w") as f:
        f.write(versionNo)

    shutil.move(f'{os.getcwd()}/spdlog', f'{os.getcwd()}/../DrEngine/vendor/spdlog')

    print('SPDLOG installed successfully!')

def DownloadPremake():
    if os.path.exists(f'{os.getcwd()}/../vendor/bin/premake'):
        print('Premake Up-to date')
        return

    print('Downloading Premake.')

    url = f'https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip'
    req = requests.get(url)

    # Check if the request was successful
    if req.status_code != 200:
        print(f'Error downloading Premake: HTTP {req.status_code}')
        print(f'Response content: {req.text[:500]}')
        exit()

    # Check if we actually got a ZIP file
    if not req.content.startswith(b'PK'):
        print('Error: Downloaded Premake content is not a ZIP file')
        print(f'Content type: {req.headers.get("content-type", "unknown")}')
        print(f'Content length: {len(req.content)}')
        print(f'First 100 bytes: {req.content[:100]}')
        exit()

    filename = url.split('/')[-1]


    with open(filename, 'wb') as output_file:
        output_file.write(req.content)

    print('Downloaded Premake.')

    print('Starting Premake Extraction')

    with zipfile.ZipFile(BytesIO(req.content)) as zf:
        zf.extract('premake5.exe', 'premake/')

    print('Premake extracted Successfully')

    print('Deleting Premake Residual Files')

    os.remove(f'{os.getcwd()}/{filename}')

    print('Downloading Premake License')

    url = f'https://raw.githubusercontent.com/premake/premake-core/master/LICENSE.txt'
    req = requests.get(url)

    with open('premake/LICENSE.txt', 'wb') as output_file:
        output_file.write(req.content)

    print('Premake License downloaded.')

    print('Finalizing Premake Setup')

    shutil.move('premake', '../vendor/bin/premake')

    print('Premake installed successfully!')

def DownloadSDLttf():
    # Get all releases and find the latest SDL2_ttf version (not SDL3_ttf)
    response = requests.get("https://api.github.com/repos/libsdl-org/SDL_ttf/releases")
    releases = response.json()
    
    # Find the latest SDL2_ttf release (version starting with "2.")
    versionNo = None
    for release in releases:
        version = release["name"]
        if version.startswith("2."):
            versionNo = version
            break
    
    if versionNo is None:
        print("Error: Could not find any SDL2_ttf releases")
        exit()

    if os.path.exists(f'{os.getcwd()}/../DrEngine/vendor/SDL2_ttf'):
        f = open(f'{os.getcwd()}/../DrEngine/vendor/SDL2_ttf/version.txt')
        if f.read() == versionNo:
            print('SDL2_ttf Up-to date')
            return
        else:
            print('!!!!!!!!!!SDL2_ttf Outdated. Delete DrEngine/Vendor folder then relaunch the script!!!!!!!!!!!!!!!!!!!')
            print(f'"{os.getcwd()}/../DrEngine/vendor"')
            exit()

    print('Downloading SDL2_ttf')

    print(f"SDL2_ttf Version: {versionNo}")

    url = f'https://github.com/libsdl-org/SDL_ttf/releases/download/release-{versionNo}/SDL2_ttf-devel-{versionNo}-VC.zip'
    req = requests.get(url)

    # Check if the request was successful
    if req.status_code != 200:
        print(f'Error downloading SDL2_ttf: HTTP {req.status_code}')
        print(f'Response content: {req.text[:500]}')
        exit()

    # Check if we actually got a ZIP file
    if not req.content.startswith(b'PK'):
        print('Error: Downloaded SDL2_ttf content is not a ZIP file')
        print(f'Content type: {req.headers.get("content-type", "unknown")}')
        print(f'Content length: {len(req.content)}')
        print(f'First 100 bytes: {req.content[:100]}')
        exit()

    filename = url.split('/')[-1]

    with open(filename, 'wb') as output_file:
        output_file.write(req.content)

    print('Downloaded SDL2_ttf.')

    print('Starting SDL2_ttf Extraction')

    with zipfile.ZipFile(BytesIO(req.content)) as zf:
        for member in tqdm(zf.infolist(), desc='Extracting SDL2_ttf '):
            try:
                zf.extract(member, os.getcwd())
            except zipfile.error as e:
                print(f'Error while extracting SDL2_ttf: {e}')
                pass

    print('SDL2_ttf extracted Successfully')

    print('Deleting SDL2_ttf Residual Files')

    os.remove(f'{os.getcwd()}/{filename}')

    print('Finalizing SDL2_ttf Setup')

    os.rename(f'SDL2_ttf-{versionNo}', 'SDL2_ttf')

    # writing version.txt
    with open('SDL2_ttf/version.txt', "w") as f:
        f.write(versionNo)

    shutil.move(f'{os.getcwd()}/SDL2_ttf', f'{os.getcwd()}/../DrEngine/vendor/SDL2_ttf')

    print('SDL2_ttf installed Successfully!')

def DownloadSDLimage():
    # Get all releases and find the latest SDL2_image version (not SDL3_image)
    response = requests.get("https://api.github.com/repos/libsdl-org/SDL_image/releases")
    releases = response.json()
    
    # Find the latest SDL2_image release (version starting with "2.")
    versionNo = None
    for release in releases:
        version = release["name"]
        if version.startswith("2."):
            versionNo = version
            break
    
    if versionNo is None:
        print("Error: Could not find any SDL2_image releases")
        exit()

    if os.path.exists(f'{os.getcwd()}/../DrEngine/vendor/SDL2_image'):
        f = open(f'{os.getcwd()}/../DrEngine/vendor/SDL2_image/version.txt')
        if f.read() == versionNo:
            print('SDL2_image Up-to date')
            return
        else:
            print('!!!!!!!!!!SDL2_image Outdated. Delete DrEngine/Vendor folder then relaunch the script!!!!!!!!!!!!!!!!!!!')
            print(f'"{os.getcwd()}/../DrEngine/vendor"')
            exit()

    print('Downloading SDL2_image')

    print(f"SDL2_image Version: {versionNo}")

    url = f'https://github.com/libsdl-org/SDL_image/releases/download/release-{versionNo}/SDL2_image-devel-{versionNo}-VC.zip'
    req = requests.get(url)

    # Check if the request was successful
    if req.status_code != 200:
        print(f'Error downloading SDL2_image: HTTP {req.status_code}')
        print(f'Response content: {req.text[:500]}')
        exit()

    # Check if we actually got a ZIP file
    if not req.content.startswith(b'PK'):
        print('Error: Downloaded SDL2_image content is not a ZIP file')
        print(f'Content type: {req.headers.get("content-type", "unknown")}')
        print(f'Content length: {len(req.content)}')
        print(f'First 100 bytes: {req.content[:100]}')
        exit()

    filename = url.split('/')[-1]

    with open(filename, 'wb') as output_file:
        output_file.write(req.content)

    print('Downloaded SDL2_image.')

    print('Starting SDL2_image Extraction')

    with zipfile.ZipFile(BytesIO(req.content)) as zf:
        for member in tqdm(zf.infolist(), desc='Extracting SDL2_image '):
            try:
                zf.extract(member, os.getcwd())
            except zipfile.error as e:
                print(f'Error while extracting SDL2_image: {e}')
                pass

    print('SDL2_image extracted Successfully')

    print('Deleting SDL2_image Residual Files')

    os.remove(f'{os.getcwd()}/{filename}')

    print('Finalizing SDL2_image Setup')

    os.rename(f'SDL2_image-{versionNo}', 'SDL2_image')

    # writing version.txt
    with open('SDL2_image/version.txt', "w") as f:
        f.write(versionNo)

    shutil.move(f'{os.getcwd()}/SDL2_image', f'{os.getcwd()}/../DrEngine/vendor/SDL2_image')

    print('SDL2_image installed Successfully!')

def DownloadSDLmixer():
    # Get all releases and find the latest SDL2_mixer version (not SDL3_mixer)
    response = requests.get("https://api.github.com/repos/libsdl-org/SDL_mixer/releases")
    releases = response.json()
    
    # Find the latest SDL2_mixer release (version starting with "2.")
    versionNo = None
    for release in releases:
        version = release["name"]
        if version.startswith("2."):
            versionNo = version
            break
    
    if versionNo is None:
        print("Error: Could not find any SDL2_mixer releases")
        exit()

    if os.path.exists(f'{os.getcwd()}/../DrEngine/vendor/SDL2_mixer'):
        f = open(f'{os.getcwd()}/../DrEngine/vendor/SDL2_mixer/version.txt')
        if f.read() == versionNo:
            print('SDL2_mixer Up-to date')
            return
        else:
            print('!!!!!!!!!!SDL2_mixer Outdated. Delete DrEngine/Vendor folder then relaunch the script!!!!!!!!!!!!!!!!!!!')
            print(f'"{os.getcwd()}/../DrEngine/vendor"')
            exit()

    print('Downloading SDL2_mixer')

    print(f"SDL2_mixer Version: {versionNo}")

    url = f'https://github.com/libsdl-org/SDL_mixer/releases/download/release-{versionNo}/SDL2_mixer-devel-{versionNo}-VC.zip'
    req = requests.get(url)

    # Check if the request was successful
    if req.status_code != 200:
        print(f'Error downloading SDL2_mixer: HTTP {req.status_code}')
        print(f'Response content: {req.text[:500]}')
        exit()

    # Check if we actually got a ZIP file
    if not req.content.startswith(b'PK'):
        print('Error: Downloaded SDL2_mixer content is not a ZIP file')
        print(f'Content type: {req.headers.get("content-type", "unknown")}')
        print(f'Content length: {len(req.content)}')
        print(f'First 100 bytes: {req.content[:100]}')
        exit()

    filename = url.split('/')[-1]

    with open(filename, 'wb') as output_file:
        output_file.write(req.content)

    print('Downloaded SDL2_mixer.')

    print('Starting SDL2_mixer Extraction')

    with zipfile.ZipFile(BytesIO(req.content)) as zf:
        for member in tqdm(zf.infolist(), desc='Extracting SDL2_mixer '):
            try:
                zf.extract(member, os.getcwd())
            except zipfile.error as e:
                print(f'Error while extracting SDL2_mixer: {e}')
                pass

    print('SDL2_mixer extracted Successfully')

    print('Deleting SDL2_mixer Residual Files')

    os.remove(f'{os.getcwd()}/{filename}')

    print('Finalizing SDL2_mixer Setup')

    os.rename(f'SDL2_mixer-{versionNo}', 'SDL2_mixer')

    # writing version.txt
    with open('SDL2_mixer/version.txt', "w") as f:
        f.write(versionNo)

    shutil.move(f'{os.getcwd()}/SDL2_mixer', f'{os.getcwd()}/../DrEngine/vendor/SDL2_mixer')

    print('SDL2_mixer installed Successfully!')

DownloadPremake()
DownloadSPDLOG()
DownloadSDL()
DownloadSDLttf()
DownloadSDLimage()
DownloadSDLmixer()

print('Setup Complete! Run GenerateProjectFiles.bat to generate Visual Studio 2022 Solution.')


