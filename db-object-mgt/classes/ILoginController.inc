<?php
interface  ILoginController {
	/**
	 * Выполнить вход
	 * @param Array $props
	 * @return 
	 * <ul>	
	 * <li>res[0] - удачно/не удачно, true/false</li>
	 * <li>res[1] - возвращаемый результат</li>
	 * <li>res[2] - сообщение об ошибке</li>
	 * </ul>
	 */
	public function login($props);
	
	public function logout($props);
	
	public function createToken($props);
	
}
?>