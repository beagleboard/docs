#!/bin/sh
sudo apt update -y && sudo apt install -y latexmk texlive-latex-recommended texlive-latex-extra texlive-fonts-recommended
pip install --user -r requirements.txt
./PRUCookbook/install.sh
