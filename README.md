# A_prime_code
Quick plotting code for The A' Team

Put these C macros in your ExRootAnalysis folder

run with e.g.
root -l 'zp_a_ana.C'

Make sure you are accessing the right input file (edit the appropriate line accordingly)

Make sure that the output file's name is how you want it (be careful because the macros will overwrite old files if you don't change the output name)

Feel free to change the binning of the plots if you need to

Feel free to add plots if you want


The particles are stored using a class named TRootLHEFParticle.  To check the contents of this class and what's available for plotting, just open the root file that you're trying to make plots from with

root -l filename.root


Then do "new TBrowser".  In the window that pops up, double click on the filename, double click on "LHEF", and double click on "Particle"