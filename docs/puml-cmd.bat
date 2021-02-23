setlocal
set invoke_java="C:\Program Files\AdoptOpenJDK\jre-15.0.2.7-hotspot\bin\java"
set puml_jar=C:\ProgramData\chocolatey\lib\plantuml\tools\plantuml.jar
set run_puml=%invoke_java% -jar %puml_jar%
%run_puml% -tsvg %1