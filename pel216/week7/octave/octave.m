1;

clear;
clf;

fpath_1 = input("Digite o nome completo para o arquivo (funcao 1): ", "s");
pontos_1 = dlmread(fpath_1, ",");
x_1 = pontos_1(:,1);
y_1 = pontos_1(:,3);

fpath_2 = input("Digite o nome completo para o arquivo (funcao 2): ", "s");
pontos_2 = dlmread(fpath_2, ",");
x_2 = pontos_2(:,1);
y_2 = pontos_2(:,3);

fpath_3 = input("Digite o nome completo para o arquivo (funcao 3): ", "s");
pontos_3 = dlmread(fpath_3, ",");
x_3 = pontos_3(:,1);
y_3 = pontos_3(:,3);

figure(1, "Position", get(0,"screensize"));

semilogx(x_1, y_1, "b");
hold on;
semilogx(x_2, y_2, "r");
hold on;
semilogx(x_3, y_3, "g");
hold off;

grid on;
grid minor on;
axis("tight");
title("Quantidade de amostras versus taxa de erro absoluto");
xlabel("Quantidade de amostras");
ylabel("Taxa de erro absoluto");
legend("f(x)=sqrt(x) [a=0, b=4]", "f(x)=4/(1+x^2) [a=0, b=1]", "f(x)=sqrt(x + sqrt(x)) [a=0, b=1]");
legend location north;
legend boxon;

# pergunta ao usuario se o grafico deve ser salvo
save = yes_or_no("Deseja salvar o JPG? ");
if save
  print (strcat("ea___monte-carlo___f1-f2-f3", ".jpg"));
endif
close();