data = load("SKMC.o");
N = data(:,1);
t = data(:,3)/3600;

Ain = 12100.0;
A = 160000.0;
Aout = A - Ain;
Din = 250;
Dout = 3500;
N_analytical = 1/(1 + Aout*Din/Ain/Dout);
pe = 100*abs(N_analytical - mean(N))/N_analytical

error = 100*abs(N - N_analytical)/N_analytical;

figure(3)
hold on
plot(t,N,'r-');
plot((0:1:14500)/3600,ones(1,14501)*N_analytical,'--g');
hold off

figure(4)
hold on
plot(t,error,'k-');
hold off

figure(5)
hold on
for(i = 0:40)
    plot(i*10*ones(1,401), 0:400, 'k-')
    plot(0:400,i*10*ones(1,401), 'k-')
end
hold off
    
