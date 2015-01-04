#!/bin/bash
################################################################################
# File: sourcefilter.sh
#
# Author: $Format:%an$
#
# Date Created: Sunday January 4, 2014
# Date Revised: $Format:%cD$
#
# Description: Doxygen source code filter to perform pattern substitution for
#              the following Git archive patterns:
#                  $Format:%an$ -> Most recent author name
#                  $Format:%cD$ -> Most recent commit date
#
#              This will allow the user to view the complete Doxygen output
#              without having the first generate a code release using the
#              'git archive' command. Only the release version number will not
#              be output on the main page, since this is selected by the user
#              when generating a code release.
#
#              Doxygen calls this file as
#                  <filter> <input-file>
################################################################################

#
# Store the most recent author name commit date of the filtered file
#
author=`git log -1 --format=%an $1`
cmtDate=`git log -1 --format=%cD $1`

#
# Perform pattern substitution for the most recent author name and commit date
#
sed -e "1,/\$Format:%an\\$/ s|\$Format:%an\\$|${author}|" \
    -e "1,/\$Format:%cD\\$/ s|\$Format:%cD\\$|${cmtDate}|" $1



































# End sourcefilter.sh
