<?php

interface ISource {
	/**
	 * Подключение к источнику данных
	 * @param mixed $params
	 */
	public function connect($params=null);
	/**
	 * Выполнение запроса к источнику данных
	 * @param mixed $params
	 */
	public function Execquery($params=null);
	/**
	 * Закрыть соединение с источником данных
	 * @param mixed $params
	 */
	public function close($params=null);
}

?>