<?php

interface IUser {
	const ID = "id";
	const LOGIN = "login";
	const PASSWORD = "password";
	const AVATAR = "avatar";
	
	private $id;
	private $login;
	private $password;
	private $permissions;
	private $avatar;
	/**
	 * Задать логин
	 */
	private function setLogin($login);
	/**
	 * Получить логин
	 */
	public function getLogin();
	/**
	 * Задать пароль
	 * @param String $password
	 * 							- шифрованая строка пароля
	 */
	private function setPassword($password);
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
	
}

?>