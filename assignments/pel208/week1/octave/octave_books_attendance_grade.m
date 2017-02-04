1;

clear;
clf;

# *****************************************************************************
fpath = input("Digite o nome completo para o arquivo: ", "s");
pontos = dlmread(fpath, "\t");
x = pontos(:,1);
y = pontos(:,2);
z = pontos(:,3);

figure(1, "Position", get(0,"screensize"));

scatter3(x, y, z);
hold on;
axis("tight");
grid on;
title("Least Squares (livros = 4, presenca = 20)");
xlabel("Livros");
ylabel("Presenca");
zlabel("Notas");

# pergunta ao usuario se o grafico deve ser salvo
save = yes_or_no("Deseja salvar o JPG? ");
if save
  print "01_amostras.jpg";
endif

X = linspace(0, 10, 20);
Y = linspace(0, 30, 60);
[XX, YY] = meshgrid(X, Y);
ZZ = 37.37919 + XX.*4.03689 + YY.*1.28348;
mesh(X, Y, ZZ);
hold on;
save = yes_or_no("Deseja salvar o JPG? ");
if save
  print "02_lsm.jpg";
endif

# inclui o ponto final
scatter3(4, 20, 79.19, 'g');
hold on;
save = yes_or_no("Deseja salvar o JPG? ");
if save
  print "03_ponto.jpg";
endif
# *****************************************************************************
