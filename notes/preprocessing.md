## PREPROCESSING 
# VMs
1. sign in to auftakt with ssh hop@auftakt, should use my private key marlehmann_syssec, not the password
2. ssh martina@130.60.193.174 (easier password)


# Metadata
- Variable list from GTEx: https://www.ncbi.nlm.nih.gov/projects/gap/cgi-bin/GetListOfAllObjects.cgi?study_id=phs000424.v5.p1&object_type=variable
- select for
	AGE
	SEX
  group with expected differential expression: SMTSD
  https://www.nature.com/articles/s41598-017-00952-9 cerebellum has the most differential expression in the brain
  --> select cerebellum vs cortex as the groups

# Algorithm
1. read in files
2. create per-bp-coverage files whilst also counting all reads, **normalize** by read count
3. create per-bp average coverage file
4. iterate over each bedgraph and identify differentially expressed regions (stored in bedgraph or in per-bp)?
   1. remove all positions with < 5 reads
   2. group regions as differentially expressed by computing moving average for a region and adding to the region if
   the new bp has +/- 10% of the moving average coverage (e.g. moving average is 50, if bp 277 has coverage 55, 
   we add it to the differentially expressed region)
   3. store in new vector (or the same as per-bp)?
   0: not differentially expressed
   -1: too few reads
   1...n: part of differentially expressed region x
   4. create vector which stores only the differentially expressed regions and their positions and th
   chrom------start--------end---------coverage (avg)---------coverage (actual)----------difference

   

# C++ Dataframe Libraries
https://github.com/hosseinmoein/DataFrame


# Git notes
- add directories I want to ignore to the .gitignore in root (mls_semesterprojekt)

process to set up repo: 
1. remove previous .git folder
2. git init in the root folder
3. git remote add origin https://github.com/martinalavanya/mls_semesterprojekt.git
4. git add .
5. git commit -m "test"
6. git push -u origin master (OR main, depending on naming)

set to SSH 
1. git remote set-url origin git@github.com:vatkruidvat/fastder.git
2. ssh -T git@github.com

diverging branches:
git pull --rebase origin initial-cpp-algorithm


make new branch
1. git checkout -b cpp_development
2. git push -u origin cpp_development (so that the branch becomes available remotely)

get username: 
	git config user.name
	git config user.email

reset interrupted git add: 
	git reset

