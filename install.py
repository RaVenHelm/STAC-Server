#!/usr/bin/env python

from urllib.request import urlopen
import tarfile as tar
import shutil
import subprocess

import sys
import os
import argparse


def download_and_install():
    deps = [
        'http://zlib.net/zlib-1.2.8.tar.gz',
        'http://www.bzip.org/1.0.6/bzip2-1.0.6.tar.gz',
        'http://downloads.sourceforge.net/project/boost/boost/1.61.0/boost_1_61_0.tar.gz',
        'https://dev.mysql.com/get/Downloads/Connector-C++/mysql-connector-c++-1.1.7-linux-ubuntu12.04-x86-64bit.tar.gz'
    ]

    for url in deps:
        file_name = url.split('/')[-1]

        request = urlopen(url)
        fh = open(file_name, 'wb')
        print('Downloading {}'.format(file_name))

        file_size_downloaded = 0
        block_size = 8192
        while True:
            buffer = request.read(block_size)
            if not buffer:
                break

            file_size_downloaded += len(buffer)
            fh.write(buffer)
            print('.', end='')

        print()
        fh.close()

        arch = tar.open(file_name)
        arch.extractall('./deps')

        os.remove(file_name)


def build_boost(out_dir):
    original_dir = os.getcwd()
    boost_dir = os.path.join(out_dir, 'boost_1_61_0')
    # bzip2_dir = os.path.join(out_dir, 'bzip2-1.0.6')
    # zlib_dir = os.path.join(out_dir, 'zlib-1.2.8')

    platform = sys.platform
    if platform.startswith('linux'):
        shutil.copy2('boost-build.sh', boost_dir)
        os.chdir(boost_dir)
        boost_build = ['bash', 'boost-build.sh', original_dir]
        subprocess.run(boost_build)
    elif platform.startswith('win32'):
        subprocess.run(['bootstrap.bat'])

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Install dependencies for the STAC Server')
    parser.add_argument('--no-download', action='store_true', default=False, help='If you already downloaded the dependencies, this is the switch for you!')
    parser.add_argument('-d', '--output-dir', default=os.path.join(os.getcwd(), 'deps'), help='Path to install directory for dependencies, defaults to the current directory + /deps')

    args = parser.parse_args()
    to_download, out_dir = (args.no_download, args.output_dir)

    if not to_download:
        download_and_install()

    build_boost(out_dir)
