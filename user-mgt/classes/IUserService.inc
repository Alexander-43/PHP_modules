<?php

interface IUserService {
	
	/**
	 * Возвращает всех пользователей
	 */
	public function getAllUsers($params);
	
	/**
	 * Создание пользователя
	 */
	public function createUser($params);
	
	/**
	 * Установить права для пользователя
	 */
	public function setPermission($params);
	
	/**
	 * Войти пользователем
	 * @param Object $params
	 * 					- параметры пользователя для входа
	 */
	public function doLogin($params);
	
	/**
	 * Выйти пользователем
	 * @param String $id
	 * 					- id пользователя для logout`a

	 */
	public function doLogout($id);
	
	/**
	 * Получение списка полей класса
	 * @param Array $vars
	 * 					- массив переменных из дочернего класса 
	 */
	public function getVars($vars = NULL);
}

?>