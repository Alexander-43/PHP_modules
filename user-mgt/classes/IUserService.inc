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
	 * @return вернем пользователя и его токен по: 
	 * <ol>
	 * <li>логин + пароль</li>
	 * <li>id</li>
	 * <li>token</li>
	 * </ol>
	 */
	public function doLogin($params);
	
	/**
	 * Выйти пользователем
	 * @param String $params
	 * 					- параметры пользователя для logout`a
	 */
	public function doLogout($params);
	
	/**
	 * Получение списка полей класса
	 * @param Array $vars
	 * 					- массив переменных из дочернего класса 
	 */
	public function getVars($vars = NULL);
}

?>