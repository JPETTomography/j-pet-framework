pipeline {
  agent any
  stages {
    stage('download source') {
      steps {
        git(url: 'https://github.com/grey277/j-pet-framework', branch: 'master')
      }
    }
    stage('download root') {
      steps {
        build 'j-pet-framework'
      }
    }
  }
}