function [cr_rfl cc_rfl] = lincr(wvl,rfl)

crbin='/Users/bbue/Research/src/C/new_cr/C/release/cr';
tmpfile='/tmp/lincr_rfl_tmp.txt';
outfile='/tmp/lincr_rfl_tmp_cr.txt';

fid = fopen(tmpfile,'w');
fprintf(fid,'%d\n',numel(wvl));
for j=1:numel(wvl)
  fprintf(fid,'%f %f\n',wvl(j),rfl(j));
end
fclose(fid);

system([crbin ' ' tmpfile ' ' outfile ' > /dev/null']);
dat = importdata(outfile,' ',1);
delete(tmpfile);

cr_rfl = dat.data(:,3);
if nargout==2
  cc_rfl = dat.data(:,4);
end
