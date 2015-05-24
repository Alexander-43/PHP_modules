<?php

interface IUser {
	const ID = "id";
	const LOGIN = "login";
	const PASSWORD = "password";
	const AVATAR = "avatar";
	
	/**
	 * Создание нового пользователя
	 * @param unknown $props
	 * 						- массив свойств
	 */
	public function create($props);
	
	/**
	 * Задать логин
	 */
	public function setLogin($login);
	/**
	 * Получить логин
	 */
	public function getLogin();
	/**
	 * Задать пароль
	 * @param String $password
	 * 							- строка пароля
	 * @param boolean $encrypt
	 * 							- шифровать
	 */
	public function setPassword($password, $encrypt);
	/**
	 * Получить шифрованую строку пароля
	 */
	public function getPassword();
	/**
	 * Получить Права пользователя
	 */
	public function getPermission();
	/**
	 * Добавить аватар
	 * @param Object $params
	 */
	public function setAvatar($params);
	/**
	 * Получить аватар
	 */
	public function getAvatar();
	/**
	 * Пользователь выполнил вход
	 */
	public function isLogged();
	/**
	 * Уникальный Id пользователя
	 */
	public function getId();
	/**
	 * Задать токен
	 */
	public function setToken($value);
	/**
	 * Получить токен
	 */
	public function getToken();
}

?>