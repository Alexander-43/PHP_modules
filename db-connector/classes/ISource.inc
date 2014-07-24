<?php

interface ISource {
	/**
	 * Подключение к БД
	 * @param mixed $params
	 */
	public function connect($params=null);
	/**
	 * Выполнить запрос
	 * @param mixed $params
	 */
	public function Execquery($params=null);
	/**
	 * Закрыть подключение к БД
	 * @param mixed $params
	 */
	public function close($params=null);
}

?>