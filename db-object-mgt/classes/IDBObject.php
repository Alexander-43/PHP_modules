<?php

interface IDBObject {
	
	/**
	 * �������� �������
	 */
	public function create();
	
	/**
	 * �������� �������
	 */
	public function delete();
	
	/**
	 * ���������� �������
	 */
	public function update();
}

?>