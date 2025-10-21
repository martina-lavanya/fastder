## PREPROCESSING 
# VMs
1. sign in to auftakt with ssh hop@auftakt, should use my private key marlehmann_syssec, not the password
2. ssh martina@130.60.193.174 (easier password)


# Git Command Overview
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
git pull --rebase origin cpp_development

remove folder from remote
1. add to .gitignore
2. git rm -r --cached <folder> (don't forget --cached, otherwise local deletion as well!)
3. git commit -m
4. git push


make new branch
1. git checkout -b cpp_development
2. git push -u origin cpp_development (so that the branch becomes available remotely)

get username: 
	git config user.name
	git config user.email

reset interrupted git add: 
	git reset


grep:

1. for a file name: find . -type f -name "filename.txt" (or find /etc/hosts -type f -name "hi.txt")
2. for a directory: find . -type d -name "dirname"
3. for a string: grep -ri "search"


commands to build:
1) install cmake, check with cmake --version
2) mkdir build
cd build
3) cmake .. (if the cmake file is one level out of the build directory)
4) make -j$(nproc) (build with multiple cores)
5) ./mls


rm -rf build
mkdir build && cd build
cmake ..
make -j$(nproc)