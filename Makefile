# Minimal makefile for Sphinx documentation
#

# You can set these variables from the command line.
SPHINXOPTS    =
SPHINXBUILD   = sphinx-build
SOURCEDIR     = .
BUILDDIR      = _build
LINKCHECKDIR  = .

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

.PHONY: help Makefile

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
%: Makefile
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

# External Link Verification

#LINKCHECKDIR  = build/linkcheck

#.PHONY: checklinks
#  checklinks:
#  $(SPHINXBUILD) -b linkcheck $(SPHINXOPTS) $(LINKCHECKDIR)
#  $(SPHINXBUILD) -b linkcheck $(LINKCHECKDIR)
#  @echo
#  @echo "Check finished. Report is in $(LINKCHECKDIR)."