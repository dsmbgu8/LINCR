dat = importdata('example/cidat.txt',' ',1);
wvl = dat.data(:,1);
rfl = dat.data(:,2);

[cr_rfl cc_rfl] = lincr(wvl,rfl);

figure(1)
subplot(211);
hold on
plot(wvl,rfl);
plot(wvl,cc_rfl,'g--');
hold off;
subplot(212);
plot(wvl,cr_rfl);

