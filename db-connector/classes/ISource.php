<?php

interface ISource {
	/**
	 * ����������� � ��������� ������
	 * @param mixed $params
	 */
	public function connect($params=null);
	/**
	 * ���������� ������� � ��������� ������
	 * @param mixed $params
	 */
	public function Execquery($params=null);
	/**
	 * ������� ���������� � ���������� ������
	 * @param mixed $params
	 */
	public function close($params=null);
}

?>