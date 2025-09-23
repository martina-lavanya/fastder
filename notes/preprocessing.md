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
	https://www.nature.com/articles/s41598-017-00952-9 cerebellum has the most differential expression
	--> select cerebellum vs cortex as the groups

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




get username: 
	git config user.name
	git config user.email

reset interrupted git add: 
	git reset

