% Carico i dati
data_debug   = readtable('times_debug.csv');
data_release = readtable('times_release.csv');

% Range comune per i panoramici
ylim_panorama = [0 1e-4];

% --- Grafico 1: panoramico Debug (scala lineare) ---
figure;
plot(data_debug.n, data_debug.bubble,    'DisplayName', 'Bubble');     hold on;
plot(data_debug.n, data_debug.insertion, 'DisplayName', 'Insertion');
plot(data_debug.n, data_debug.selection, 'DisplayName', 'Selection');
plot(data_debug.n, data_debug.merge,     'DisplayName', 'Merge');
plot(data_debug.n, data_debug.quick,     'DisplayName', 'Quick');
plot(data_debug.n, data_debug.hybrid,    'DisplayName', 'Hybrid');
plot(data_debug.n, data_debug.std_sort,  'DisplayName', 'std::sort');
xlabel('n'); ylabel('Tempo medio (s)');
title('Panoramica - Debug');
ylim(ylim_panorama);
legend('Location', 'northwest');
grid on;
exportgraphics(gcf, 'panorama_debug.png', 'Resolution', 150);

% --- Grafico 2: panoramico Release (scala lineare, stessi limiti) ---
figure;
plot(data_release.n, data_release.bubble,    'DisplayName', 'Bubble');     hold on;
plot(data_release.n, data_release.insertion, 'DisplayName', 'Insertion');
plot(data_release.n, data_release.selection, 'DisplayName', 'Selection');
plot(data_release.n, data_release.merge,     'DisplayName', 'Merge');
plot(data_release.n, data_release.quick,     'DisplayName', 'Quick');
plot(data_release.n, data_release.hybrid,    'DisplayName', 'Hybrid');
plot(data_release.n, data_release.std_sort,  'DisplayName', 'std::sort');
xlabel('n'); ylabel('Tempo medio (s)');
title('Panoramica - Release');
ylim(ylim_panorama);
legend('Location', 'northwest');
grid on;
exportgraphics(gcf, 'panorama_release.png', 'Resolution', 150);

% --- Grafico 3: zoom sugli algoritmi veloci - Debug (scala lineare) ---
figure;
plot(data_debug.n, data_debug.insertion, 'DisplayName', 'Insertion');     hold on;
plot(data_debug.n, data_debug.quick,     'DisplayName', 'Quick');
plot(data_debug.n, data_debug.hybrid,    'DisplayName', 'Hybrid');
plot(data_debug.n, data_debug.std_sort,  'DisplayName', 'std::sort');
xlabel('n'); ylabel('Tempo medio (s)');
title('Algoritmi veloci - Debug');
ylim([0 5e-5]);
legend('Location', 'northwest');
grid on;
exportgraphics(gcf, 'zoom_debug.png', 'Resolution', 150);

% --- Grafico 4: zoom sugli algoritmi veloci - Release (scala lineare) ---
figure;
plot(data_release.n, data_release.insertion, 'DisplayName', 'Insertion');     hold on;
plot(data_release.n, data_release.quick,     'DisplayName', 'Quick');
plot(data_release.n, data_release.hybrid,    'DisplayName', 'Hybrid');
plot(data_release.n, data_release.std_sort,  'DisplayName', 'std::sort');
xlabel('n'); ylabel('Tempo medio (s)');
title('Algoritmi veloci - Release');
ylim([0 1e-5]);
legend('Location', 'northwest');
grid on;
exportgraphics(gcf, 'zoom_release.png', 'Resolution', 150);