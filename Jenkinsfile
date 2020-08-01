pipeline {
    agent any
    options {
        timeout(time: 10, unit: 'MINUTES')
        timestamps()
    }

    stages {
        stage('Build') {
            steps {
              withCredentials([usernamePassword(credentialsId: 'b93384a9-c09d-42b6-b8f1-adb1f4e045c6', passwordVariable: 'GIT_PASSWORD', usernameVariable: 'GIT_USERNAME')]) {
                sh("""
                  git config --global credential.username ${GIT_USERNAME}
                  git config --global credential.helper "!echo password=${GIT_PASSWORD}; echo"
                  git config --global advice.detachedHead false
                  export PLATFORMIO_CORE_DIR=.
                  export PLATFORMIO_CACHE_DIR=.
                  pio upgrade
                  sed -i \'/default_envs/d\' platformio.ini
                  pio run

                """)
              }
            }
        }
     }
     post {
            always {
              echo 'Cleaning up workspace'
              deleteDir() /* clean up our workspace */
            }
            failure {
              emailext (
                attachLog: true, 
                body: '''${SCRIPT, template="groovy-html.template"}''', 
                subject: "${env.JOB_NAME} FAILED - Build # ${env.BUILD_NUMBER}", 
                mimeType: 'text/html',
                to: 'basschouten65@gmail.com'
              )
            }
            fixed {
              emailext (
                to: 'basschouten65@gmail.com',
                body: '''${SCRIPT, template="groovy-html.template"}''', 
                subject: "${env.JOB_NAME} Back to Normal - Build # ${env.BUILD_NUMBER}", 
                mimeType: 'text/html',
                attachLog: true
              )
            }           
        } 
}
