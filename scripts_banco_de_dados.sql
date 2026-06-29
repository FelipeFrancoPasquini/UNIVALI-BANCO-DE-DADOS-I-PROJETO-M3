-- Criação e utilização do Banco de Dados
CREATE DATABASE IF NOT EXISTS steam_db;
USE steam_db;

-- Criação das Tabelas
CREATE TABLE IF NOT EXISTS Usuario (
    id_usuario INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    data_cadastro DATE NOT NULL
);

CREATE TABLE IF NOT EXISTS Categoria (
    id_categoria INT AUTO_INCREMENT PRIMARY KEY,
    nome_categoria VARCHAR(50) NOT NULL
);

CREATE TABLE IF NOT EXISTS Jogo (
    id_jogo INT AUTO_INCREMENT PRIMARY KEY,
    titulo VARCHAR(100) NOT NULL,
    preco DECIMAL(10, 2) NOT NULL,
    id_categoria INT,
    FOREIGN KEY (id_categoria) REFERENCES Categoria(id_categoria)
);

CREATE TABLE IF NOT EXISTS Biblioteca (
    id_usuario INT,
    id_jogo INT,
    data_aquisicao DATE NOT NULL,
    PRIMARY KEY (id_usuario, id_jogo),
    FOREIGN KEY (id_usuario) REFERENCES Usuario(id_usuario),
    FOREIGN KEY (id_jogo) REFERENCES Jogo(id_jogo)
);

-- Populando tabelas

INSERT IGNORE INTO Categoria (id_categoria, nome_categoria) VALUES 
(1, 'RPG'), 
(2, 'Aventura'), 
(3, 'Estratégia'), 
(4, 'FPS'), 
(5, 'Outras');

INSERT INTO Usuario (nome, email, data_cadastro) VALUES 
('Joao Silva', 'joao@outlook.com', '2026-06-29'),
('Ana Almeida', 'ana@gmail.com', '2026-06-29');

INSERT INTO Jogo (titulo, preco, id_categoria) VALUES 
('Elden Ring', 249.90, 1),
('God of War', 199.90, 2),
('Counter-Strike', 0.00, 4);

INSERT INTO Biblioteca (id_usuario, id_jogo, data_aquisicao) VALUES 
(1, 1, '2026-06-29'),
(1, 2, '2026-06-29'),
(2, 3, '2026-06-29');
