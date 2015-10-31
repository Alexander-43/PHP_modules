<?php
interface  ILoginController {
	/**
	 * Выполнить вход
	 * @param Array $props
	 * @return 
	 * 	res[0] - удачно/не удачно, true/false
	 * 	res[1] - возвращаемый результат
	 * 	res[2] - ообщение об ошибке
	 */
	public function login($props);
	
	public function logout($props);
	
	public function createToken($props);
}
?>