1;

clear;
clf;

# *****************************************************************************
# https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data
# *****************************************************************************
fpath = input("Digite o nome completo para o arquivo: ", "s");
c = dlmread(fpath, ",");
c1 = c(c(:,end) == 0, 1:4);
c2 = c(c(:,end) == 1, 1:4);
c3 = c(c(:,end) == 2, 1:4);

m1 = transpose(mean(c1));
m2 = transpose(mean(c2));
m3 = transpose(mean(c3));

s1 = cov(c1); 
s2 = cov(c2); 
s3 = cov(c3);
sw = s1 + s2 + s3;
mu = (m1 + m2 + m3) ./ 3;

n1 = n2 = n3 = 4;
sb1 = n1 .* (m1-mu)*transpose(m1-mu);
sb2 = n2 .* (m2-mu)*transpose(m2-mu);
sb3 = n3 .* (m3-mu)*transpose(m3-mu);
sb = sb1 + sb2 + sb3;

invsw = inv(sw);
invsw_by_sb = invsw * sb;

[v,d]=eig(invsw_by_sb);

new_c = transpose(transpose(v(:,1:2)) * transpose(c(:,1:4)));

# *****************************************************************************



# *****************************************************************************
# Distribuicao SL vs SW
# *****************************************************************************
hold on;
scatter(c1(:,1), c1(:,2), 10, 'r', '^'); 
scatter(c2(:,1), c2(:,2), 10, 'g', 's'); 
scatter(c3(:,1), c3(:,2), 10, 'b', 'o'); 
hold off;
axis("tight");
title("Distribuicao das classes (SL vs SW)");
xlabel("Sepal length");
ylabel("Sepal width");
legend('Setosa', 'Versicolor', 'Virginica');
legend boxon;
print("distribuicao_sl-vs-sw.jpg");
close();
# *****************************************************************************



# *****************************************************************************
# Distribuicao PL vs PW
# *****************************************************************************
hold on;
scatter(c1(:,3), c1(:,4), 10, 'r', '^'); 
scatter(c2(:,3), c2(:,4), 10, 'g', 's'); 
scatter(c3(:,3), c3(:,4), 10, 'b', 'o'); 
hold off;
axis("tight");
title("Distribuicao das classes (PL vs PW)");
xlabel("Petal length");
ylabel("Petal width");
legend('Setosa', 'Versicolor', 'Virginica', 'location', 'southeast');
legend boxon;
print("distribuicao_pl-vs-pw.jpg");
close();
# *****************************************************************************



# *****************************************************************************
# histograma SL
# *****************************************************************************
hold on; 
hist(c1(:,1), "r");
hist(c2(:,1), "g");
hist(c3(:,1), "b");
hold off;
axis("tight");
title("Histograma (SL)");
xlabel("Sepal length");
legend('Setosa', 'Versicolor', 'Virginica');
legend boxon;
print("histograma_sl.jpg");
close();
# *****************************************************************************


# *****************************************************************************
# histograma SW
# *****************************************************************************
hold on; 
hist(c1(:,2), "r");
hist(c2(:,2), "g");
hist(c3(:,2), "b");
hold off;
axis("tight");
title("Histograma (SW)");
xlabel("Sepal width");
legend('Setosa', 'Versicolor', 'Virginica');
legend boxon;
print("histograma_sw.jpg");
close();
# *****************************************************************************



# *****************************************************************************
# histograma PL
# *****************************************************************************
hold on; 
hist(c1(:,3), "r");
hist(c2(:,3), "g");
hist(c3(:,3), "b");
hold off;
axis("tight");
title("Histograma (PL)");
xlabel("Petal length");
legend('Setosa', 'Versicolor', 'Virginica');
legend boxon;
print("histograma_pl.jpg");
close();
# *****************************************************************************


# *****************************************************************************
# histograma PW
# *****************************************************************************
hold on; 
hist(c1(:,4), "r");
hist(c2(:,4), "g");
hist(c3(:,4), "b");
hold off;
axis("tight");
title("Histograma (PW)");
xlabel("Petal width");
legend('Setosa', 'Versicolor', 'Virginica');
legend boxon;
print("histograma_pw.jpg");
close();
# *****************************************************************************


# *****************************************************************************
# Novos valores
# *****************************************************************************
hold on; 
scatter(new_c(   1:50,1), new_c(   1:50,2), 10, 'r', '^'); 
scatter(new_c( 51:100,1), new_c( 51:100,2), 10, 'g', 's'); 
scatter(new_c(101:150,1), new_c(101:150,2), 10, 'b', 'o'); 
hold off;
axis("tight");
title("Distribuicao das classes (LDA1 e LDA2)");
xlabel("LDA 1");
ylabel("LDA 2");
legend('Setosa', 'Versicolor', 'Virginica', 'location', 'southeast');
legend boxon;
print("distribuicao_lda1_lda2.jpg");
close();
# *****************************************************************************