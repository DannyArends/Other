#
# install.libs.R
# copyright (c) 2011 Danny Arends
# 
# doDMDcompilation is run when the package is build/installed/checked
#

doDMDcompilation <- function(command){
  if(system(command)==0){
    cat("** DMD compiler found\n")
  }else{
    cat("** WARNING: No DMD compiler found\n")
  }
}

#Compile the D files in the source folder
Dfiles <- paste(Sys.glob(c("D/*.d","D/dll/*","D/libs/*")),collapse=" ")
if(WINDOWS){
  doDMDcompilation(paste("dmd -ofDdll.dll -L/IMPLIB  -O -inline -release ",Dfiles," phobos.lib -IC:/D/dmd2/windows/bin",sep=""))
}else{
  doDMDcompilation(paste("dmd -ofDdll.so ",Dfiles," phobos.lib",sep=""))
}

#Get all the files that were compiled and the output location
files <- Sys.glob(paste("*", SHLIB_EXT, sep=''))
libarch <- if (nzchar(R_ARCH)) paste('libs', R_ARCH, sep='') else 'libs'

#Install the package
dest <- file.path(R_PACKAGE_DIR, libarch)
dir.create(dest, recursive = TRUE, showWarnings = FALSE)
file.copy(files, dest, overwrite = TRUE)

#Clean up the compiled files and such
file.remove(Sys.glob(paste("*", SHLIB_EXT, sep='')))
file.remove(Sys.glob("*.o"))
file.remove(Sys.glob("*.lib"))
file.remove(Sys.glob("*.obj"))
