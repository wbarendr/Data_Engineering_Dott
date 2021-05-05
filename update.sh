#!/bin/bash

B1=`cat b_total_rides_info`
NEW_FILES=`cat Deduplication_logic_new_CSV_files`

cp FILES_DAILY_UPDATED/* LOG_FILES

echo -n "LOG_FILES/data-engineer-test-rides" > rides.txt
date '+_%B_%d_%Y' >> rides.txt
R1=`cat rides.txt`

echo -n "LOG_FILES/data-engineer-test-users" > users.txt
date '+_%B_%d_%Y' >> users.txt
U1=`cat users.txt`

mv LOG_FILES/data-engineer-test-rides "$R1"
mv LOG_FILES/data-engineer-test-users "$U1"


echo "Updating raw data files..."
# psql -U wester -d postgres -c "$NEW_FILES"

echo "CREATING MAIN TABLE..."
# psql -U wester -d postgres -c "$B1"

echo "Logging data-engineer-test-rides with date to s3 cloud"
# aws s3 mv "$R1" s3://dott-assignment-data-engineer
echo "Logging data-engineer-test-users with date to s3 cloud"
# aws s3 mv "$U1" s3://dott-assignment-data-engineer

# Don't forget to extend the june table beyond june 2019

rm users.txt
rm rides.txt