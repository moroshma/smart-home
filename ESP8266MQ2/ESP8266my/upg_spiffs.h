const char charCR = '\r';
const char charLF = '\n';
const char charSlash = '/';
const char charSpace = ' ';
const char charDot = '.';
const char charComma = ',';
const char charColon = ':';
const char charSemicolon = ';';
const char charQuote = '"';
const char charApostroph = '\'';
const char charOpenBrace = '{';
const char charCloseBrace = '}';
const char charEqual = '=';
const char charLess = '<';
const char charGreater = '>';

const char* const strEmpty = "";
const char* const strSlash = "/";

const char* const pathSPIFFS PROGMEM = "/spiffs";
const char* const pathUpdate PROGMEM = "/update";
const char* const pathWiFi PROGMEM = "/wifi";
const char* const pathStore PROGMEM = "/store";
const char* const pathReboot PROGMEM = "/reboot";
const char* const pathData PROGMEM = "/data";

const char* const textPlain PROGMEM = "text/plain";
const char* const textHtml PROGMEM = "text/html";
const char* const textJson PROGMEM = "text/json";

const char* const fileNotFound PROGMEM = "FileNotFound";
const char* const indexHtml PROGMEM = "index.html";

const char* const headerTitleOpen PROGMEM = "<!DOCTYPE html>\n\
<html>\n\
<head>\n\
<title>";
const char* const headerTitleClose PROGMEM = "</title>\n";
const char* const headerStyleOpen PROGMEM = "<style type=\"text/css\">\n";
const char* const headerStyleClose PROGMEM = "</style>\n";
const char* const headerStyleExtOpen PROGMEM = "<link rel=\"stylesheet\" href=\"";
const char* const headerStyleExtClose PROGMEM = "\">\n";
const char* const headerScriptOpen PROGMEM = "<script type=\"text/javascript\">\n";
const char* const headerScriptClose PROGMEM = "</script>\n";
const char* const headerScriptExtOpen PROGMEM = "<script type=\"text/javascript\" src=\"";
const char* const headerScriptExtClose PROGMEM = "\"></script>\n";
const char* const headerBodyOpen PROGMEM = "</head>\n\
<body";
const char* const footerBodyClose PROGMEM = "</body>\n\
</html>";
const char* const inputTypeOpen PROGMEM = "<input type=\"";
const char* const inputNameOpen PROGMEM = " name=\"";
const char* const inputValueOpen PROGMEM = " value=\"";
const char* const simpleTagClose PROGMEM = " />";
const char* const typeText PROGMEM = "text";
const char* const typePassword PROGMEM = "password";
const char* const typeRadio PROGMEM = "radio";
const char* const typeButton PROGMEM = "button";
const char* const typeSubmit PROGMEM = "submit";
const char* const typeReset PROGMEM = "reset";
const char* const typeHidden PROGMEM = "hidden";
const char* const typeFile PROGMEM = "file";
const char* const extraChecked PROGMEM = "checked";

const char* const jsonFreeHeap PROGMEM = "freeheap";
const char* const jsonUptime PROGMEM = "uptime";

const char bools[2][6] PROGMEM = { "false", "true" };

const char* const paramApMode PROGMEM = "apmode";
const char* const paramSSID PROGMEM = "ssid";
const char* const paramPassword PROGMEM = "password";
const char* const paramDomain PROGMEM = "domain";
const char* const paramReboot PROGMEM = "reboot";

const uint16_t maxStringLen = 32;
//---------------------------------------------------------------------------------
String webPageStyle(const String& style, bool file)
{
  String result;

  if (file)
  {
    result = FPSTR(headerStyleExtOpen);
    result += style;
    result += FPSTR(headerStyleExtClose);
  }
  else
  {
    result = FPSTR(headerStyleOpen);
    result += style;
    result += FPSTR(headerStyleClose);
  }

  return result;
}


//--------------------------------------------------------------------------------
String webPageBody(const String& extra)
{
  String result = FPSTR(headerBodyOpen);
  result += charSpace;
  result += extra;
  result += charGreater;
  result += charLF;

  return result;
}
//--------------------------------------------------------------------------------
String webPageEnd()
{
  String result = FPSTR(footerBodyClose);

  return result;
}
//--------------------------------------------------------------------------------
String escapeQuote(const String& str)
{
  String result;
  int start = 0, pos;

  while (start < str.length()) {
    pos = str.indexOf(charQuote, start);
    if (pos != -1) {
      result += str.substring(start, pos) + F("&quot;");
      start = pos + 1;
    } else {
      result += str.substring(start);
      break;
    }
  }

  return result;
}

//-------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------
String tagInput(const String& type, const String& name, const String& value, const String& extra)
{
  String result = FPSTR(inputTypeOpen);

  result += type;
  result += charQuote;
  if (name != strEmpty) {
    result += FPSTR(inputNameOpen);
    result += name;
    result += charQuote;
  }
  if (value != strEmpty) {
    result += FPSTR(inputValueOpen);
    result += escapeQuote(value);
    result += charQuote;
  }
  result += charSpace;
  result += extra;
  result += FPSTR(simpleTagClose);

  return result;
}
//--------------------------------------------------------------------------------
String webPageBody()
{
  String result = FPSTR(headerBodyOpen);
  result += charGreater;
  result += charLF;

  return result;
}
//--------------------------------------------------------------------------------
String webPageScript(const String& script, bool file)
{
  String result;

  if (file)
  {
    result = FPSTR(headerScriptExtOpen);
    result += script;
    result += FPSTR(headerScriptExtClose);
  }
  else
  {
    result = FPSTR(headerScriptOpen);
    result += script;
    result += FPSTR(headerScriptClose);
  }

  return result;
}
//--------------------------------------------------------------------------------

String webPageStart(const String& title)
{
  String result;
  result = F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  result += F("<meta charset=\"utf-8\">");
  result += FPSTR(headerTitleOpen);
  result += title;
  result += FPSTR(headerTitleClose);
  return result;
}
//---------------------------------------------------
String getContentType(const String& fileName)
{
  if (server.hasArg(F("download")))
    return String(F("application/octet-stream"));
  else if (fileName.endsWith(F(".htm")) || fileName.endsWith(F(".html")))
    return String(FPSTR(textHtml));
  else if (fileName.endsWith(F(".css")))
    return String(F("text/css"));
  else if (fileName.endsWith(F(".js")))
    return String(F("application/javascript"));
  else if (fileName.endsWith(F(".png")))
    return String(F("image/png"));
  else if (fileName.endsWith(F(".gif")))
    return String(F("image/gif"));
  else if (fileName.endsWith(F(".jpg")) || fileName.endsWith(F(".jpeg")))
    return String(F("image/jpeg"));
  else if (fileName.endsWith(F(".ico")))
    return String(F("image/x-icon"));
  else if (fileName.endsWith(F(".xml")))
    return String(F("text/xml"));
  else if (fileName.endsWith(F(".pdf")))
    return String(F("application/x-pdf"));
  else if (fileName.endsWith(F(".zip")))
    return String(F("application/x-zip"));
  else if (fileName.endsWith(F(".gz")))
    return String(F("application/x-gzip"));

  return String(FPSTR(textPlain));
}

//----------------------------------------------------------------------------------
bool handleFileRead(const String& path)
{
  String fileName = path;
  if (fileName.endsWith(strSlash))
    fileName += FPSTR(indexHtml);
  String contentType = getContentType(fileName);
  String pathWithGz = fileName + F(".gz");
  if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(fileName))
  {
    if (SPIFFS.exists(pathWithGz))
      fileName = pathWithGz;
    File file = SPIFFS.open(fileName, "r");
    size_t sent = server.streamFile(file, contentType);
    file.close();

    return true;
  }

  return false;
}
//--------------------------------------------------------------------------------
//-------------------------------------------------------------
void handleNotFound()
{
  LoginContr();

  if (! handleFileRead(server.uri()))
    server.send(404, FPSTR(textPlain), FPSTR(fileNotFound));
}
//----------------------------------------------------------------------------------------
void handleFileUploaded()
{
  LoginContr();
  Serial.println("successful");
  server.send(200, FPSTR(textHtml), F("<META http-equiv=\"refresh\" content=\"2;URL=\">Upload successful."));
}
//----------------------------------------------------------------------------------------
void handleFileUpload()
{
  LoginContr();
  Serial.print(F("handleFile"));
  static File uploadFile;

  if (server.uri() != FPSTR(pathSPIFFS)) return;
  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    String filename = upload.filename;
    if (! filename.startsWith(strSlash)) filename = charSlash + filename;
    Serial.print("handleFileUpload Name: "); Serial.println(filename);
    uploadFile = SPIFFS.open(filename, "w");
    filename = String();
  }
  else if (upload.status == UPLOAD_FILE_WRITE)
  { Serial.print("handleFileUpload Data: "); Serial.println(upload.currentSize);
    if (uploadFile) uploadFile.write(upload.buf, upload.currentSize);
  }
  else if (upload.status == UPLOAD_FILE_END)
  {
    if (uploadFile) uploadFile.close();
    Serial.print("handleFileUpload Size: "); Serial.println(upload.totalSize);

  }
  //SPIFFS.format();
}
//----------------------------------------------------------------------------------------
void handleFileDelete()
{
  LoginContr();
  if (server.args() == 0)
    return server.send(500, FPSTR(textPlain), F("BAD ARGS"));
  String path = server.arg(0);
  if (path == strSlash)
    return server.send(500, FPSTR(textPlain), F("BAD PATH"));
  if (! SPIFFS.exists(path))
    return server.send(404, FPSTR(textPlain), FPSTR(fileNotFound));
  SPIFFS.remove(path);
  server.send(200, FPSTR(textPlain), strEmpty);
  path = String();
}
//----------------------------------------------------------------------------------------
void handleSPIFFS()
{
  LoginContr();
  String script = F("function openUrl(url, method) {\n\
var request = new XMLHttpRequest();\n\
request.open(method, url, false);\n\
request.send(null);\n\
if (request.status != 200)\n\
alert(request.responseText);\n\
}\n\
function getSelectedCount() {\n\
var inputs = document.getElementsByTagName(\"input\");\n\
var result = 0;\n\
for (var i = 0; i < inputs.length; i++) {\n\
if (inputs[i].type == \"checkbox\") {\n\
if (inputs[i].checked == true)\n\
result++;\n\
}\n\
}\n\
return result;\n\
}\n\
function updateSelected() {\n\
document.getElementsByName(\"delete\")[0].disabled = (getSelectedCount() > 0) ? false : true;\n\
}\n");

  script += F("function deleteSelected() {\n\
var inputs = document.getElementsByTagName(\"input\");\n\
for (var i = 0; i < inputs.length; i++) {\n\
if (inputs[i].type == \"checkbox\") {\n\
if (inputs[i].checked == true)\n\
openUrl(\"");

  script += FPSTR(pathSPIFFS);
  script += F("?filename=/\" + encodeURIComponent(inputs[i].value), \"DELETE\");\n\
}\n\
}\n\
location.reload(true);\n\
}\n");

  String page = webPageStart(F("SPIFFS"));
  page += webPageScript(script, false);
  page += webPageBody();
  page += F("<form method=\"POST\" action=\"\" enctype=\"multipart/form-data\" onsubmit=\"if (document.getElementsByName('upload')[0].files.length == 0) { alert('No file to upload!'); return false; }\">\n\
<h3>SPIFFS</h3>\n\
<p>\n");

  Dir dir = SPIFFS.openDir("/");
  int cnt = 0;
  while (dir.next()) {
    cnt++;
    String fileName = dir.fileName();
    size_t fileSize = dir.fileSize();
    if (fileName.startsWith(strSlash))
      fileName = fileName.substring(1);
    page += F("<input type=\"checkbox\" name=\"file");
    page += String(cnt);
    page += F("\" value=\"");
    page += fileName;
    page += F("\" onchange=\"updateSelected()\" /><a href=\"/");
    page += fileName;
    page += F("\" download>");
    page += fileName;
    page += F("</a>\t");
    page += String(fileSize);
    page += F("<br/>\n");
  }
  page += String(cnt);
  page += F(" file(s)<br/>\n\
<p>\n");
  page += tagInput(FPSTR(typeButton), F("delete"), F("Delete"), F("onclick=\"if (confirm('Are you sure to delete selected file(s)?') == true) deleteSelected()\" disabled"));
  page += F("\n\
<p>\n\
Upload new file:<br/>\n");
  page += tagInput(FPSTR(typeFile), F("upload"), strEmpty, "");
  page += charLF;
  page += tagInput(FPSTR(typeSubmit), strEmpty, F("Upload"), "");

  page += F("<p>");
  page += F("<input type=\"button\" value=\"Назад\"  onclick=\"location.href='/'\">");

  page += F("\n\
</form>\n");
  page += webPageEnd();

  server.send(200, FPSTR(textHtml), page);
}

//-----------------------------------------------------------------------------------------
void handleUpdate()
{
  LoginContr();
  String page = webPageStart(F("Sketch Update"));
  page += webPageBody();
  page += F("<form method=\"POST\" action=\"\" enctype=\"multipart/form-data\" onsubmit=\"if (document.getElementsByName('update')[0].files.length == 0) { alert('No file to update!'); return false; }\">\n\
Select compiled sketch to upload:<br/>\n");
  page += tagInput(FPSTR(typeFile), F("update"), strEmpty, "");
  page += charLF;
  page += tagInput(FPSTR(typeSubmit), strEmpty, F("Update"), "");
  page += "<p>";
  page += "<input type=\"button\" value=\"Назад\"  onclick=\"location.href='/'\">";
  page += F("\n\
</form>\n");
  page += webPageEnd();

  server.send(200, FPSTR(textHtml), page);
}
//----------------------------------------------------------------------------------------
void handleSketchUpdated()
{
  LoginContr();
  static const char* const updateFailed PROGMEM = "Update failed!";
  static const char* const updateSuccess PROGMEM = "<META http-equiv=\"refresh\" content=\"15;URL=\">Update successful! Rebooting...";

  server.send(200, FPSTR(textHtml), Update.hasError() ? FPSTR(updateFailed) : FPSTR(updateSuccess));

  ESP.restart();
}
//-----------------------------------------------------------------------------------------
void handleSketchUpdate()
{
  LoginContr();
  if (server.uri() != FPSTR(pathUpdate))
    return;
  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START)
  {
    WiFiUDP::stopAll();
    Serial.print(F("Update sketch from file \""));
    Serial.print(upload.filename.c_str());
    Serial.println(charQuote);
    uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
    if (! Update.begin(maxSketchSpace)) { // start with max available size
      Update.printError(Serial);
    }
  }
  else if (upload.status == UPLOAD_FILE_WRITE)
  {
    Serial.print(charDot);
    if (Update.write(upload.buf, upload.currentSize) != upload.currentSize)
    {
      Update.printError(Serial);
    }
  }
  else if (upload.status == UPLOAD_FILE_END)
  {
    if (Update.end(true)) { // true to set the size to the current progress
      Serial.println();
      Serial.print(F("Updated "));
      Serial.print(upload.totalSize);
      Serial.println(F(" byte(s) successful. Rebooting..."));
    }
    else
    {
      Update.printError(Serial);
    }
  }
  else if (upload.status == UPLOAD_FILE_ABORTED)
  {
    Update.end();
    Serial.println(F("\nUpdate was aborted"));
  }
  yield();
}
//-----------------------------------------------------------------------------------------------------
void h_wifi()//wifi
{
  LoginContr();
  String message = F("<!DOCTYPE html>\n");
  message += F("<html>\n");
  message += F("<head>\n");
  message += F("<title>Установка Wi-Fi</title>\n");
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n");
  message += F("<meta charset=\"utf-8\">\n");
  message += F("<style type=\"text/css\">");
  message += F(".adressfild {width: 35px; text-align: center;}");
  message += F("</style>");
  message += F("<script type=\"text/javascript\">\n");
  message += F("function openUrl(url) {\n");
  message += F("var request = new XMLHttpRequest();\n");
  message += F("request.open('GET', url, true);\n");
  message += F("request.send(null);\n ");
  message += F("};\n ");

  message += F("</script>");
  message += F("</head>\n");
  message += F("<body>\n");
  message += F("<form name=\"wifi\" method=\"get\" action=\"/save\">\n");
  message += F("<h3>Настройка Wi-Fi</h3>\n");
  message += F("<br />");
  message += F("<input type = \"checkbox\" name=\"ApMode\" id=\"ApMode\" ");
  if (ApMode == true) message += F(" checked=\"checked\"");
  message += F("onchange=\"openUrl('/switch?ApMode=' + this.checked);\" ");
  message += F("<label for=\"ApMode\"> esp в режиме точки доступа (AP)</label>");
  message += F("<p>");

  message += F("Имя сети (SSID):<br/>\n");
  message += F("<input type=\"text\" name=\"");
  message += F("ssid");
  message += F("\" maxlength=");
  message += String(maxStrParamLength);
  message += F(" value=\"");
  message += quoteEscape(ssid);
  message += F("\" />\n");
  message += F("<br/>\n");
  message += F("Пароль:<br/>\n");
  message += F("<input type=\"password\" name=\"");
  message += F("password");
  message += F("\" maxlength=");
  message += String(maxStrParamLength);
  message += F(" value=\"");
  message += quoteEscape(password);
  message += F("\" />\n");

  message += F("<br/>");

  message += F("<p>Присвоить ip-адрес<br/>");
  message += F("<input name=\"ip1\" type=\"text\" class=\"adressfild\" value=\""); message += String(ip1) + F("\" maxlength=\"3\" />");
  message += F("<input name=\"ip2\" type=\"text\" class=\"adressfild\" value=\""); message += String(ip2) + F("\" maxlength=\"3\" />");
  message += F("<input name=\"ip3\" type=\"text\" class=\"adressfild\" value=\""); message += String(ip3) + F("\" maxlength=\"3\" />");
  message += F("<input name=\"ip4\" type=\"text\" class=\"adressfild\" value=\""); message += String(ip4) + F("\" maxlength=\"3\" />");
  message += F("<p>\n");
  message += F("<p>Маска подсети<br/>");
  message += F("<input name=\"ms1\" type=\"text\" class=\"adressfild\" value=\""); message += String(ms1) + F("\" maxlength=\"3\" />");
  message += F("<input name=\"ms2\" type=\"text\" class=\"adressfild\" value=\""); message += String(ms2) + F("\" maxlength=\"3\" />");
  message += F("<input name=\"ms3\" type=\"text\" class=\"adressfild\" value=\""); message += String(ms3) + F("\" maxlength=\"3\" />");
  message += F("<input name=\"ms4\" type=\"text\" class=\"adressfild\" value=\""); message += String(ms4) + F("\" maxlength=\"3\" />");
  message += F("<p>\n");
  message += F("<p>Основной шлюз<br/>");
  message += F("<input name=\"gt1\" type=\"text\" class=\"adressfild\" value=\""); message += String(gt1) + F("\" maxlength=\"3\" />");
  message += F("<input name=\"gt2\" type=\"text\" class=\"adressfild\" value=\""); message += String(gt2) + F("\" maxlength=\"3\" />");
  message += F("<input name=\"gt3\" type=\"text\" class=\"adressfild\" value=\""); message += String(gt3) + F("\" maxlength=\"3\" />");
  message += F("<input name=\"gt4\" type=\"text\" class=\"adressfild\" value=\""); message += String(gt4) + F("\" maxlength=\"3\" />");
  message += F("<p>\n");
  message += F("<p>Использовать DNS-сервер<br/>");
  message += F("<input name=\"dn1\" type=\"text\" class=\"adressfild\" value=\""); message += String(dn1) + F("\" maxlength=\"3\" />");
  message += F("<input name=\"dn2\" type=\"text\" class=\"adressfild\" value=\""); message += String(dn2) + F("\" maxlength=\"3\" />");
  message += F("<input name=\"dn3\" type=\"text\" class=\"adressfild\" value=\""); message += String(dn3) + F("\" maxlength=\"3\" />");
  message += F("<input name=\"dn4\" type=\"text\" class=\"adressfild\" value=\""); message += String(dn4) + F("\" maxlength=\"3\" />");
  message += F("<p>\n");

  message += F("<input type = \"checkbox\" name=\"AccessMode\" id=\"AccessMode\" ");
  if (AccessMode == true) message += F(" checked=\"checked\"");
  message += F("onchange=\"openUrl('/switch?AccessMode=' + this.checked);\" ");
  message += F("<label for=\"AccessMode\"> требуется авторизация</label>");
  message += F("<br />");

  message += F("Логин для входа на ESP:<br/>\n");
  message += F("<input type=\"text\" name=\"AccessLogin\" maxlength=");
  message += String(maxStrParamLength);
  message += F(" value=\"");
  message += String(AccessLogin);
  message += F("\" />");
  message += F("<br/>");

  message += F("Пароль для входа на ESP:<br/>\n");
  message += F("<input type=\"password\" name=\"");
  message += F("AccessPassword");
  message += F("\" maxlength=");
  message += String(maxStrParamLength);
  message += F(" value=\"");
  message += String(AccessPassword);
  message += F("\" />");
  message += F("<br/>");

  message += F("<p><br/>");
  message += F("<input type=\"button\" value=\"Назад\" onclick=\"location.href='/'\">");
  message += F("<input type=\"submit\" value=\"Сохранить\" />\n");
  message += F("<input type=\"hidden\" name=\"");
  message += F("reboot");
  message += F("\" value=\"1\" />\n");
  message += F("</form>\n");
  message += F("</body>\n");
  message += F("</html>");

  server.send(200, F("text/html"), message);
}
//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
void h_mqtt()//mqtt
{
  LoginContr();
  String message = F("<!DOCTYPE html>\n");
  message += F("<html>\n");
  message += F("<head>\n");
  message += F("<title>Настройка MQTT</title>\n");
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n");
  message += F("<meta charset=\"utf-8\">\n");
  message += F("<style type=\"text/css\">");
  message += F(".adressfild {width: 35px; text-align: center;}");
  message += F("</style>");
  message += F("<script type=\"text/javascript\">\n");
  message += F("function openUrl(url) {\n");
  message += F("var request = new XMLHttpRequest();\n");
  message += F("request.open('GET', url, true);\n");
  message += F("request.send(null);\n ");
  message += F("};\n ");
  message += refreshTempMessage("mqtt");
  message += F("function refresh(){\n");
  message +=   F("var request = new XMLHttpRequest();\n");
  message +=   F("request.open('GET', '/data_mainPage', true);\n");
  message +=   F("request.onreadystatechange = function(){\n");
  message +=       F("if (request.readyState == 4) {\n");
  message +=         F("var data = JSON.parse(request.responseText);\n ");
  message +=         F("document.getElementById('MQTT').innerHTML = data.MQTT;\n");
  message +=         F("}};\n");
  message +=   F("request.send(null);\n");
  message +=   F("}\n");
  message += F("setInterval(refresh, 1000);\n");
  message += F("</script>");
  message += F("</head>\n");
  message += F("<body>\n");
  message += F("<form name=\"mqtt\" method=\"get\" action=\"/save\">\n");
  message += F("<h3>Настройка MQTT</h3>\n");
  message += F("<br />");
  message += F("MQTT: <span id=\"MQTT\">.</span></p>\n");
  message += F("<input type = \"checkbox\" name=\"useMQTT\" id=\"useMQTT\" ");
  if (useMQTT == true) message += F(" checked=\"checked\"");
  message += F("onchange=\"openUrl('/switch?useMQTT=' + this.checked);\" ");
  message += F("<label for=\"useMQTT\"> включить MQTT</label>");
  message += F("<p>");

  message += F("<input type=\"text\" name=\"mqttServer\" maxlength="); message += String(maxStrParamLength) + F(" value=\"");
  message += String(mqttServer) + F("\" /> Адрес сервера<br/>\n");
  message += F("<input type=\"text\" name=\"mqttServerPort\" maxlength="); message += String(maxStrParamLength) + F(" value=\"");
  message += String(mqttServerPort) + F("\" /> Порт<br/>");
  message += F("<input type=\"text\" name=\"mqttUser\" maxlength="); message += String(maxStrParamLength) + F(" value=\"");
  message += String(mqttUser) + F("\" /> Имя пользователя<br/>");
  message += F("<input type=\"text\" name=\"mqttUserPassword\" maxlength="); message += String(maxStrParamLength) + F(" value=\"");
  message += String(mqttUserPassword) + F("\" /> Пароль<br/>");
  message += F("<input type=\"text\" name=\"mqttClientId\" maxlength="); message += String(maxStrParamLength) + F(" value=\"");
  message += String(mqttClientId) + F("\" /> ClientId (MQTT)<br/>");

  message += F("<input type=\"text\" name=\"mqttReconnectSec\" maxlength="); message += String(maxStrParamLength) + F(" value=\"");
  message += String(mqttReconnectSec) + F("\" /> Переподключение, сек<br/>");


  message += F("<input type=\"button\" value=\"Подключить\" onclick=\"openUrl('/switch?mqtt_conn=1');\">");

  message += F("<p><br/>");
  message += F("<input type=\"button\" value=\"Назад\" onclick=\"location.href='/'\">");
  message += F("<input type=\"submit\" value=\"Сохранить\" />\n");
  message += F("<input type=\"hidden\" name=\"reboot\" value=\"1\" />\n");
  message += F("</form>\n");
  message += F("</body>\n");
  message += F("</html>");

  server.send(200, F("text/html"), message);
}
//--------------------------------------------------------------------------------------
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String s, s_payload;
  Serial.print(F("MQTT message arrived ["));
  Serial.print(topic);
  Serial.print(F("] "));
  for (int i = 0; i < length; i++) {
    s_payload += (char)payload[i];
    Serial.print((char)payload[i]);
  }
  Serial.println();


  s = String(topic); s.replace(F("/"), "");
  if (s.indexOf(F("swt1")) != -1) {
    switch ((char)payload[0]) {
      case '0':
        swt1 = false;
        break;
      case '1':
        swt1 = true;
        break;

    }
  }
  else if (s.indexOf(F("swt2")) != -1) {
    switch ((char)payload[0]) {
      case '0':
        swt2 = false;
        break;
      case '1':
        swt2 = true;
        break;

    }
  }
  else if (s.indexOf(F("swt3")) != -1) {
    switch ((char)payload[0]) {
      case '0':
        swt3 = false;
        break;
      case '1':
        swt3 = true;
        break;
    }
  }
  else if (s.indexOf(F("swt4")) != -1) {
    switch ((char)payload[0]) {
      case '0':
        swt4 = false;
        break;
      case '1':
        swt4 = true;
        break;
    }
  }
}
//-------------------------------------------------------------------

void h_reboot() {
  Serial.println(F("/reboot()"));

  String message =
    F("<!DOCTYPE html>\n\
<html>\n\
<head>\n\
  <title>Rebooting</title>\n\
  <meta http-equiv=\"refresh\" content=\"1; /index.html\">\n\
  <meta charset=\"utf-8\">\
</head>\n\
<body>\n\
  Перезагрузка...\n\
</body>\n\
</html>");

  server.send(200, F("text/html"), message);

  ESP.restart();
}

//--------------------------------------------------------------------------------------
/*void handleGetTime() {
  uint32_t now = getTime();
  String page;

  page += charOpenBrace;
  page += charQuote;
  page += FPSTR(jsonUnixTime);
  page += F("\":");
  page += String(now);
  if (now) {
    int8_t hh, mm, ss;
    uint8_t wd;
    int8_t d, m;
    int16_t y;

    parseUnixTime(now, hh, mm, ss, wd, d, m, y);
    page += F(",\"");
    page += FPSTR(jsonDate);
    page += F("\":\"");
    page += dateToStr(d, m, y);
    page += F("\",\"");
    page += FPSTR(jsonTime);
    page += F("\":\"");
    page += timeToStr(hh, mm, ss);
    page += charQuote;
  }
  page += charCloseBrace;

  httpServer->send(200, FPSTR(textJson), page);
  }*/
void setTime(uint32_t now) {
  Serial.println(now);
  Serial.println(millis());

}
//-------------------------------------------------------
void handleSetTime() {
  Serial.print(F("/settime("));
  Serial.print(server.arg("time"));
  Serial.println(')');
  //parseUnixTime(server.arg("time").toInt()+timeZone*3600, R_hour, R_min, R_sec, R_wd, R_day, R_month, R_year);
  startTime = server.arg("time").toInt() + timeZone * 3600;
  startMs = millis();
  setTimeAccompl = 1;
  server.send(200, F("text/html"), "ok");
}
//-------------------------------------------------------
void handleTimeConfig()
{
  LoginContr();
  String message;

  message = F("<!DOCTYPE html>");
  message += F("<html>");
  message += F("<head>");
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  message += F("<meta charset=\"utf-8\">");
  message += F("<style type=\"text/css\">");
  message += F(".timefild {width: 35px; text-align: center;}");
  message += F("</style>");
  message += F("<script type=\"text/javascript\">");
  message += F("function openUrl(url) {\n");
  message += F("var request = new XMLHttpRequest();\n");
  message += F("request.open('GET', url, true);\n");
  message += F("request.send(null);\n ");
  message += F("};\n ");
  message += F("function updateTime() {");
  message += F("openUrl('/settime?time=' + Math.floor(Date.now() / 1000) + '&dummy=' + Date.now());\n");
  message += F("}");

  message += F("function refreshData(){\n");
  message +=   F("var request = new XMLHttpRequest();\n");
  message +=   F("request.open('GET', '/data_mainPage', true);\n");
  message +=   F("request.onreadystatechange = function(){\n");
  message +=       F("if (request.readyState == 4) {\n");
  message +=         F("var data = JSON.parse(request.responseText);\n ");
  message +=         F("document.getElementById('timeStr').innerHTML = data.timeStr;}};\n");
  message +=   F("request.send(null);\n");
  message +=   F("}\n");
  message += F("setInterval(refreshData, 1000);\n");
  message += F("</script>");
  message += F("</head>");
  message += webPageBody();
  message += F("<form name=\"time\" method=\"get\" action=\"/save\">");
  message += F("<b>Установки синхронизации времени</b><p>\n");
  message += F("<span id=\"timeStr\">.</span><p>\n");
  message += F("<input type = \"checkbox\" name=\"ntpUpd\" id=\"ntpUpd\" title=\"обновлять время по NTP\"");
  if (ntpUpd == 1) message += " checked=\"checked\"";
  message += F("onchange=\"openUrl('/switch?ntpUpd=' + this.checked);\" ");
  message += F("<label for=\"ntpUpd\">Обновлять время по NTP</label>");

  message += F("<br>\n");
  message += F("<input id=\"ntpServer1\" name=\"ntpServer1\" type=\"text\" value=\"");
  message += ntpServer1;
  message += F("\" maxlength=\"32\"/> NTP 1<br/>\n");
  message += F("<input id=\"ntpServer2\" name=\"ntpServer2\" type=\"text\" value=\"");
  message += ntpServer2;
  message += F("\" maxlength=\"32\"/> NTP 2<br/>\n");
  message += F("<input id=\"ntpServer3\" name=\"ntpServer3\" type=\"text\" value=\"");
  message += ntpServer3;
  message += F("\" maxlength=\"32\"/> NTP 3<br/>\n");
  message += F("<input id=\"updateInterval\" name=\"updateInterval\" type=\"text\" value=\"");
  message += String(updateInterval);
  message += F("\" maxlength=\"10\"/> Интервал,c<br/>\n");
  message += F("<select name=\"");
  message += F("timeZone");
  message += F("\" size=1>\n");
  for (int8_t i = -11; i <= 13; i++) {
    message += F("<option value=\"");
    message += String(i);
    message += charQuote;
    if (timeZone == i)  message += F(" selected");
    message += charGreater;
    message += F("GMT");
    if (i > 0) message  += '+';
    message += String(i);
    message += F("</option>\n");
  }
  message += F("</select> Временная зона<p>\n");
  //message += F("<br>\n");
  message += F("<input type=\"button\" value=\"Обновить время из браузера\" onclick=\"updateTime();\" /><br>\n");
  message += F("<br>\n");
  message += F("<input type=\"button\" value=\"Назад\" onclick=\"location.href='/'\">");
  message += F("<input type=\"submit\" value=\"Сохранить\" />\n");
  message += F("<input type=\"hidden\" name=\"");
  message += F("reboot");
  message += F("\" value=\"1\" />\n");
  message += F("</form>\n");
  message += F("</body>\n");
  message += F("</html>");

  server.send(200, F("text/html"), message);
}


