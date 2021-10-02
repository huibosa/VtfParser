# remove suffix
rename '_1' '' *
rename '_final' '17' *
# remove prefix
perl-rename 's/.+_//' *
# format
perl-rename 's/Pass([0-9])$/Pass0\1/g' *

# move file to upper directory
for dir in Pass*; do
  cd ${dir} && mv ./results/* ./ && rmdir results
  cd ..
done

# generate vtf filename list
find ./ -type f -name "*.vtf" | sort > vtfFiles

# generate csv
cp $HOME/Packages/VtfParser/main ./
./main < vtfFiles

# delete dummy file
find ./ -type f ! -name '*.csv' -delete
