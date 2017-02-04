1;

clear;
clf;

# *****************************************************************************
fpath = input("Digite o nome completo para o arquivo: ", "s");
pontos = dlmread(fpath, "\t");
x = pontos(:,3);
y = pontos(:,2);

figure(1, "Position", get(0,"screensize"));

scatter(x, y);
hold on;
axis("tight");
grid on;
title("Least Squares (temp = 200F)");
xlabel("Temperatura");
ylabel("Pressao");

# pergunta ao usuario se o grafico deve ser salvo
save = yes_or_no("Deseja salvar o JPG? ");
if save
  print "01_amostras.jpg";
endif

x_lsm = [190:0.1:220];
y_lsm = -81.06373 + x_lsm.*0.52289;
plot(x_lsm, y_lsm, 'r');
hold on;
save = yes_or_no("Deseja salvar o JPG? ");
if save
  print "02_lsm.jpg";
endif

# inclui o ponto final
scatter(200, 23.51, 'g');
hold on;
save = yes_or_no("Deseja salvar o JPG? ");
if save
  print "03_ponto.jpg";
endif
# *****************************************************************************
