-- Criação e utilização da tabela:
CREATE DATABASE IF NOT EXISTS steam_db;
USE steam_db;

-- Criação das tabelas e seus respectivos campos:
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

-- Inserção de dados:
INSERT IGNORE INTO Categoria (id_categoria, nome_categoria) VALUES 
(1, 'RPG'), (2, 'Aventura'), (3, 'Estratégia'), (4, 'FPS'), (5, 'Outras');
