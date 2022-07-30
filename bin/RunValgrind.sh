#!/bin/bash

# Convenience script for running Valgrind

#Set Script Name variable
SCRIPT=`basename ${BASH_SOURCE[0]}`

#Set fonts for Help.
NORM=`tput sgr0`
BOLD=`tput bold`
REV=`tput smso`


# Constants
php_version="7.3"

# Option variables

flagEnv=""
phpini=/etc/php/$php_version/cli/php.ini

# Misc

defineopt=""
definefile=""
suppresionfile=""
executeopt=""
targetpath=""
phpargs=""
scriptargs=""
outputfile=""
outputformat="text"
formatopt=""
flagPreview=""
flagEnv=""

#Help function
function ShowHelp {
  echo -e \\n"Help documentation for ${BOLD}${SCRIPT}.${NORM}"\\n
  echo -e \\n"${BOLD}Run a PHP script through valigrind${NORM}"\\n
  echo -e "${REV}Basic usage:${NORM} ${BOLD}install/bin/revea $SCRIPT --Execute MyScript.php${NORM}"\\n
  echo -e "Command line switches are optional. The following switches are recognized."
  echo -e "${REV}-c|--PhpIni${NORM}  --Path to php.ini file"
  echo -e "${REV}-d|--Define${NORM}  --Define custom ini value. See php -d option"
  echo -e "${REV}-D|--DefineFile${NORM}  --Text file contain list of arguments for -d"
  echo -e "${REV}-e|--Environment${NORM}  --Print environment to screen"
  echo -e "${REV}-f|--Format${NORM}   -- Output form (xml or text, default is text)"
  echo -e "${REV}-o|--Output${NORM} -- Full path of valgrind output file"
  echo -e "${REV}-p|--Preview${NORM} -- Preview (just show the command that will be run)"
  echo -e "${REV}-s|--SuppressionFile${NORM} --Path to valigrin suppression file"
  echo -e "${REV}-x|--Execute${NORM} --Run the given PHP script"
  echo -e "${REV}-- Arguments after -- are passed to the PHP script${NORM}"
  echo ""
  cat <<DESCRIPTIONXXX
  A wrapper script for Valgrind on a PHP script. Used primarily for testing
  PHP extensions.

  -D|--DefineFiles is optional full path to text file of form option=value (e.g. extension=foo.so)
  -e|--Environment just dumps the script environment and exits. Sometimes useful. 
  -p|--Preview sets preview mode. It is sometime useful to inspect the valgrind and
    PHP script options before running
  -s|--SupressionFile is full path to Valgrind suppression file (optional)
  -x|--Execute is path relative to current directory, or absolute path, 
       of PHP script to execute

  The -f xml option will cause the valgrind log to be written in XML. This 
  is for use with GUI tools like valkyries

DESCRIPTIONXXX
  exit 1
}

function errorHelp {
  echo -e "${REV}ERROR: $1 ${NORM}"
  ShowHelp
}

function errorMessage {
  echo -e "${REV}ERROR: $1${NORM}"
  exit 1
}

function fileDefines {
  defpart=""
  if [ ! -z $definefile ]; then
    while IFS=read -r line; do
      defpart="$defpart -d $line "
    done < $definefile
  fi
  echo $defpart
}


function assembleDefines 
{
  if [ -z "$defineopt" -a -z "$definefile" ]; then
    return
  fi

  fileDefines=$(fileDefines)
  define1=""
  if [ ! -z "$defineopt" ]; then
    define1="-d $defineopt"
  fi
  totalDefines="$fileDefines $define1"
  echo $totalDefines
}

# Produce a path name relative to REVADIR
function getScriptPath {
  scriptname=$1
  scriptpath="$scriptname"

  # Check to see if this is an absolute path
  # If relative, make full path based on $PWD
  if [ "$scriptpath" == "${scriptpath#/}" ]; then
    # Relative path
    scriptpath=$PWD/$scriptname
  fi
  echo "$scriptpath"
}

function ParseOpts {

  # “a” and “arga” have optional arguments with default values.
  # “b” and “argb” have no arguments, acting as sort of a flag.
  # “c” and “argc” have required arguments.

  # temp=`getopt -o a::bhc: --long arga::,argb,help,argc: -n $SCRIPT -- "$@"`

  temp=`getopt -o hepc:d:D:f:o:s:x: --long help,Environment,Preview,PhpIni:,Define:,DefineFile:,Format:,Output:,SuppressionFile:,Execute: -n $SCRIPT -- "$@"`
  eval set -- "$temp"
  while true; do 
    case "$1" in 
      -e|--Environment) flagEnv="1"; shift ;;
      -p|--preview) flagPreview="1"; shift ;;
      -c|--PhpIni)
        case "$2" in
          "") shift 2 ;;
          *) phpini=$2; shift 2 ;;
        esac;;
      -d|--Define)
        case "$2" in
          "") shift 2 ;;
          *) defineopt=$2; shift 2 ;;
        esac;;
      -D|--DefineFile)
        case "$2" in
          "") shift 2 ;;
          *) definefile=$2; shift 2 ;;
        esac;;
      -f|--Format)
        case "$2" in
          "") shift 2 ;;
          *) outputformat=$2; shift 2 ;;
        esac;;
      -s|--SuppressionFile)
        case "$2" in
          "") shift 2 ;;
          *) suppressionfile=$2; shift 2 ;;
        esac;;
      -o|--Output)
        case "$2" in
          "") shift 2 ;;
          *) outputfile=$2; shift 2 ;;
        esac;;
      -x|--Execute)
        case "$2" in
          "") shift 2 ;;
          *) executeopt=$2; shift 2 ;;
        esac;;
      -h|--help) ShowHelp;;
      --) shift; break ;;
      *) echo "Internal error"; exit 1 ;;
    esac;
  done

  if [ ! -z "$flagEnv" ]  ; then
    # Just dump the environment and exit
    env
    exit 0
  fi

  if [ -z "$executeopt" ]; then
    errorHelp "-x|--Execute required"
  fi

  targetpath=$(getScriptPath $executeopt)
  if [ ! -f "$targetpath" ]; then
   errorMessage "Specified php script is not accessible: $targetpath"
  fi

  if [ ! -f "$phpini" ]; then
    errorMessage "Specified php.ini file not accessible: $phpini"
  fi

  if [ ! -z "$definefile" ]; then
    if [ ! -f "$definefile" ]; then
      errorMessage "Sprecified define file not accessible: $definefile"
    fi
  fi

  if [ ! -z "$suppressionfile" ]; then
    if [ ! -f "$suppressionfile" ]; then
      errorMessage "Sprecified suppresion file not accessible: $suppressionfile"
    fi
  fi

  if [ "$outputformat" != "text" ]; then
    if [ "$outputformat" == "xml" ]; then
      if [ -z "$outputfile" ]; then
        xmlfile="valgrind.xml"
      else
        xmlfile="$outputfile.xml"
      fi
      formatopt="--xml=yes --xml-file=$xmlfile"
    else
      errorHelp "Invalid output file format given: $outputformat"
    fi
  fi



  if [ ! -z "$outputfile" ]; then 
    if [ -f "$outputfile" ]; then
      rm -f $outputfile
    fi
  fi

  scriptargs="$@"
}

function Main {
  defines=$(assembleDefines)
  suppressions=""
  if [ ! -z "$suppersionfile" ]; then
    suppressions="--suppressions=$suppressionfile"
  fi

  if [ ! -z "$scriptargs" ]; then
    argstoscript=" --  $scriptargs"
  fi

  phpiniopt=""
  if [ ! -z "$phpini" ]; then
    phpiniopt="-c $phpini"
  fi

  logopt=""
  if [ ! -z "$outputfile" ]; then
    logopt="--log-file=$outputfile"
  fi

  cmd="ZEND_DONT_UNLOAD_MODULES=1 USE_ZEND_ALLOC=0 valgrind --leak-check=full --show-leak-kinds=all --show-reachable=yes $logopt $formatopt $suppressions --track-origins=yes /usr/bin/php $phpiniopt $defines -f $targetpath $argstoscript"

  if [ ! -z "$flagPreview" ]; then
    echo -e \\n\\n"${REV}PREVIEW MODE${NORM}"
    echo -e \\n\\n$cmd\\n\\n
  else
    echo -e \\n\\n$cmd\\n\\n
    eval $cmd
  fi
}

ParseOpts $@
Main
