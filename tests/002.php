<?php
$config = array(
	"application" => array(
		"directory" => realpath(dirname(__FILE__)),
		"dispatcher" => array(
			"catchException" => 0,
			"throwException" => 1,
		),
        "modules" => "module",
	),
);

class IndexController extends Yext_AbstractController
{
    public function longNameAction()
    {
    }

    // public function indexAction() {
    //     $this->forward("controller", "dummy");
    //     return FALSE; /* don't auto-render */
    // }

    // public function dummyAction() {
    //     Yaf_Dispatcher::getInstance()->enableView();
    // }
}

$reqStr = '/module/index/long-name';
$app = new Yaf_Application($config);
$request = new Yaf_Request_Http($reqStr);

try {
    $app->getDispatcher()->registerPlugin(new Yext_Plugin());
    $app->getDispatcher()->returnResponse(false)->dispatch($request);
} catch (Yaf_Exception $e) {
    echo $e->getMessage(), "\n";
}
