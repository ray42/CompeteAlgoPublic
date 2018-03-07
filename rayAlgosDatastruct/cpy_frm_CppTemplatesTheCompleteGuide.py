#!/usr/bin/env python3

import os 
from pathlib import Path
from shutil import copyfile
import shutil

# These have to be relative to the root folder
SRCBASE = "CppTemplatesTheCompleteGuide" # EDIT THIS
DSTBSAE = os.path.basename(os.path.dirname(os.path.realpath(__file__)))

# These have to be relative to the base given above.
SRCTEX = "notes"                                  # EDIT THIS
DSTTEX = "notes"                                  # EDIT THIS

############################################################################
# Set up directory paths
############################################################################
# I've decided to use the following convention:
# [desc][name/path]_[path/str]
# desc - description of what this variable is
# name/path - choose one. Describes if this is a path, e.g. /home/ray/folder
#                         or a single name: folder
# path/str - choose one. Describes if this is a real path, or a string.

# current directory
currpath_str = os.path.dirname(os.path.realpath(__file__))

# root directory
rootpath_str = "/home/ray/learning"

# source and destination BASE directories - does not include root
srcbasename_str = SRCBASE
destbasename_str = DSTBSAE

srcbasepath_str= rootpath_str + "/" + srcbasename_str
destbasepath_str= rootpath_str + "/" + destbasename_str

# Notes directory - does not include root
# This is where the tex files are found
# THESE HAVE TO BE RELATIVE TO THE BASE PATH DESCRIBED ABOVE. FOR EXAMPLE
# IF THE BASE-RELATIVE PATH IS
# resume/f1/f2/texfiles
# then this should be: "f1/f2/texfiles"
srctexname_str = SRCTEX
desttexname_str = DSTTEX

srctexpath_str = srcbasepath_str + "/" + srctexname_str
desttexpath_str = destbasepath_str + "/" + desttexname_str


############################################################################
# Copy over .gitignore and lxterminalsetup.sh if they do not already exist
############################################################################

def copy_if_do_not_exist(srcdir, destdir, filename):
    filepath = Path(destdir+"/"+filename)
    if not filepath.is_file() :
        copyfile(srcdir+"/"+filename, destdir+"/"+filename)

copy_if_do_not_exist(srcbasepath_str, destbasepath_str, ".gitignore")
copy_if_do_not_exist(srcbasepath_str, destbasepath_str, "lxterminalsetup.sh")


############################################################################
# copy over source latex files
############################################################################

def rrcopy_single_file(srcdir, destdir, filename):
    filepath = Path(destdir+"/"+filename)
    copyfile(srcdir+"/"+filename, destdir+"/"+filename)

# This makes the destination folder if it does not already exist
def rrcopy_filelist(srcdir, destdir, filelist):

    # check if destination folder exist. If not, make it.
    destdir_path = Path(destdir)
    if not destdir_path.is_dir():
        os.makedirs(destdir_path)

    for filename in filelist:
        rrcopy_single_file(srcdir, destdir, filename)

###################################

# top level of the tex directory
somefilelist=["cleanall.sh",
              ".gitignore",
              "kbordermatrix.sty",
              "useful_vim.txt",
              "main.tex",
              "oneoff.utf-8.add",
              "README.md",
              "runlatexmk.sh",
              "crun.sh",
              "to_open.sh"]
rrcopy_filelist(srctexpath_str,desttexpath_str,somefilelist)
###################################

# Now we deal with the following directories:
# Aux - copy all
# Bibliographies - copy all
# Bin - copy all
# Codes - copy navier_stokes_preconditioners.cc,
#              navier_stokes_preconditioners.h,
#              sq_lgr_simple.cc
# Contents - copy abstract.tex
#                 contents.tex
#                 introduction.tex
# Graphs - copy C4N1_max_subarray.ps
#               tempfile
# Images - copy tempfile
# Tables - copy tempfile
# Temp - copy compilepdf
#             Makefile
#             texcountoutput.tex
# Tikz - copy all. Note that this might need to be changed in the future if
#                  I have a lot of stuff in here. But I want to keep these
#                  as good templates

# https://stackoverflow.com/questions/1868714/how-do-i-copy-an-entire-directory-of-files-into-an-existing-directory-using-pyth
def rrcopytree(src, dst, rrfolder, symlinks=False, ignore=None):
    src=src+rrfolder
    dst=dst+rrfolder
    dstpath=Path(dst)
    if not dstpath.is_dir():
        os.makedirs(dstpath)

    for item in os.listdir(src):
        s = os.path.join(src, item)
        d = os.path.join(dst, item)
        if os.path.isdir(s):
            shutil.copytree(s, d, symlinks, ignore)
        else:
            shutil.copy2(s, d)

# Aux
rrcopytree(srctexpath_str,desttexpath_str,"/Aux")

# Bibliographies
rrcopytree(srctexpath_str,desttexpath_str,"/Bibliographies")

# Bin
rrcopytree(srctexpath_str,desttexpath_str,"/Bin")

# Codes
somefilelist=["navier_stokes_preconditioners.cc",
              "navier_stokes_preconditioners.h",
              "sq_lgr_simple.cc"]
rrcopy_filelist(srctexpath_str+"/Codes",desttexpath_str+"/Codes",
                somefilelist)

# Contents
somefilelist=["abstract.tex",
              "contents.tex",
              "introduction.tex"]
rrcopy_filelist(srctexpath_str+"/Contents",desttexpath_str+"/Contents",
                somefilelist)

# Graphs
somefilelist=["C4N1_max_subarray.ps",
              "tempfile"]
rrcopy_filelist(srctexpath_str+"/Graphs",desttexpath_str+"/Graphs",
                somefilelist)

# Images
somefilelist=["tempfile"]
rrcopy_filelist(srctexpath_str+"/Images",desttexpath_str+"/Images",
                somefilelist)

# Tables
somefilelist=["tempfile"]
rrcopy_filelist(srctexpath_str+"/Tables",desttexpath_str+"/Tables",
                somefilelist)

# Temp
somefilelist=["compilepdf",
              "Makefile",
              "texcountoutput.tex"]
rrcopy_filelist(srctexpath_str+"/Temp",desttexpath_str+"/Temp",
                somefilelist)

# Tikz
rrcopytree(srctexpath_str,desttexpath_str,"/Tikz")

############################################################################
# Now we do more_notes and src from the base directory

# more_notes
somefilelist=["tempfile"]
rrcopy_filelist(srcbasepath_str+"/more_notes",
                destbasepath_str+"/more_notes",
                somefilelist)

####################################
# src

srcsrcpath_str=srcbasepath_str+"/src"
dstsrcpath_str=destbasepath_str+"/src"

# files
somefilelist=["GCCFLAGS",
              ".gitignore",
              "rayheader.h",
              "runmakeclean.sh",
              "run.sh"]
rrcopy_filelist(srcsrcpath_str,dstsrcpath_str,
                somefilelist)

# folders
rrcopytree(srcsrcpath_str,dstsrcpath_str,"/common")

# folders per chapter
folderlist=["ch1", "ch2"]
chfilelist=["drivers.sh",
            "genmake.sh",
            "run.sh",
            "test.cpp"]
for f in folderlist:
  rrcopy_filelist(srcsrcpath_str+"/"+f,dstsrcpath_str+"/"+f,
                  chfilelist)

if __name__ == '__main__':
    print("Hello from main")

