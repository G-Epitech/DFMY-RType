BINARIES = ['client', 'server']
BINARIES_TARGETS = [
    'client': 'r-type_client',
    'server': 'r-type_server',
]
BINARIES_TESTS = [
    'client': 'r-type_client_tests',
    'server': 'r-type_server_tests'
]
LIBS = ['abra', 'ECS-sdk']
LIBS_TARGETS = [
    'abra': [
        'target': 'abra',
        'type': 'shared'
    ],
    'ECS-sdk': [
        'target': 'r-type_ECS_sdk',
        'type': 'shared'
    ]
]
LIBS_TESTS = [
    'abra': 'abra_tests',
    'ECS-sdk': 'r-type_ECS_sdk_tests'
]

pipeline {
    agent none
    stages {
/*         stage ('Check style') {
            parallel {

                stage ('Lint') {
                    agent {
                        dockerfile {
                            filename 'ci/style.dockerfile'
                        }
                    }

                    steps {
                        sh 'make lint'
                    }
                }

                stage ('Format') {
                    agent {
                        dockerfile {
                            filename 'ci/style.dockerfile'
                        }
                    }
                    steps {
                        sh 'make format-check'
                    }
                }
            }
        }

        stage ('Build and tests') {
            parallel {
                stage('Linux environment') {
                    agent {
                        dockerfile {
                            filename 'ci/unix.dockerfile'
                            reuseNode true
                        }
                    }

                    stages {
                        stage('Generate build files') {
                            steps {
                                script {
                                    sh 'cmake --preset=unix:release -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$PWD/bin'
                                }
                            }
                        }

                        stage('Project binaries') {
                            steps {
                                script {
                                    for (binary in BINARIES) {
                                        def TARGET_BINARY = BINARIES_TARGETS[binary]
                                        def TARGET_TEST = BINARIES_TESTS[binary]

                                        stage ("Build and test ${binary}") {
                                            sh "cmake --build build/unix/release --target ${TARGET_BINARY}"
                                            fileExists("bin/${TARGET_BINARY}")
                                            sh "cmake --build build/unix/release --target ${TARGET_TEST}"
                                            sh "bin/${TARGET_TEST}"
                                        }
                                    }
                                }
                            }
                        }

                        stage('Project libraries') {
                            steps {
                                script {
                                    for (lib in LIBS) {
                                        def TARGET_LIB = LIBS_TARGETS[lib]['target']
                                        def TARGET_LIB_EXT = LIBS_TARGETS[lib]['type'] == 'shared' ? 'so' : 'a'
                                        def TARGET_TEST = LIBS_TESTS[lib]

                                        stage ("Build and test ${lib}") {
                                            sh "cmake --build build/unix/release --target ${TARGET_LIB}"
                                            fileExists("bin/${TARGET_LIB}.${TARGET_LIB_EXT}")
                                            sh "cmake --build build/unix/release --target ${TARGET_TEST}"
                                            sh "bin/${TARGET_TEST}"
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                stage('Windows environment') {
                    agent {
                        label 'windows'
                    }

                    stages {
                        stage('Checkout') {
                            steps {
                                checkout scm
                            }
                        }

                        stage('Generate build files') {
                            steps {
                                script {
                                    bat 'cmake --preset=windows:release -DCMAKE_RUNTIME_OUTPUT_DIRECTORY="%cd%\\bin"'
                                }
                            }
                        }

                        stage('Project libraries') {
                            steps {
                                script {
                                    for (lib in LIBS) {
                                        def TARGET_LIB = LIBS_TARGETS[lib]['target']
                                        def TARGET_LIB_EXT = LIBS_TARGETS[lib]['type'] == 'shared' ? 'dll' : 'lib'
                                        def TARGET_TEST = LIBS_TESTS[lib]

                                        stage ("Build and test ${lib}") {
                                            bat "cmake --build build/windows/release --config release --target ${TARGET_LIB}"
                                            fileExists("bin/${TARGET_LIB}.${TARGET_LIB_EXT}")
                                            bat "cmake --build build/windows/release --config release --target ${TARGET_TEST}"
                                            bat "bin\\${TARGET_TEST}.exe"
                                        }
                                    }
                                }
                            }
                        }

                        stage('Project binaries') {
                            steps {
                                script {
                                    for (binary in BINARIES) {
                                        def TARGET_BINARY = BINARIES_TARGETS[binary]
                                        def TARGET_TEST = BINARIES_TESTS[binary]

                                        stage ("Build and test ${binary}") {
                                            bat "cmake --build build/windows/release --config release --target ${TARGET_BINARY}"
                                            fileExists("bin/${TARGET_BINARY}.exe")
                                            bat "cmake --build build/windows/release --config release --target ${TARGET_TEST}"
                                            bat "bin\\${TARGET_TEST}.exe"
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } */

        stage ('Publish') {
            input {
                message "What is the new version ?"
                ok "Submit"
                parameters {
                    string(defaultValue: '1', name: 'VERSION', trim: true)
                }
            }
            parallel {
/*                 stage('Linux environment') {
                    agent {
                        dockerfile {
                            filename 'ci/unix.dockerfile'
                            reuseNode true
                        }
                    }
                } */

                stage('Windows environment') {
                    agent {
                        label 'windows'
                    }

                    stages {
/*                         stage('Generate build files') {
                            steps {
                                script {
                                    stage('Client') {
                                        bat 'cmake --preset=windows:release -DINSTALL_CLIENT=ON -DINSTALL_SERVER=OFF -U CMAKE_RUNTIME_OUTPUT_DIRECTORY'
                                        bat 'cmake --build build/windows/release --config release --target r-type_client'
                                        bat 'cd build/windows/release && cpack -C release'
                                    }
                                    stage('Server') {
                                        bat 'cmake --preset=windows:release -DINSTALL_CLIENT=OFF -DINSTALL_SERVER=ON -U CMAKE_RUNTIME_OUTPUT_DIRECTORY'
                                        bat 'cmake --build build/windows/release --config release --target r-type_server'
                                        bat 'cd build/windows/release && cpack -C release'
                                    }
                                }
                            }
                        } */

                        stage('Version') {
                            steps {
                                echo "NEW VERSION IS $VERSION"
                            }
                        }

                        stage('Create Release') {
                            steps {
                                script {
/*                                     createGitHubRelease {
                                        repository: 'G-Epitech/DFMY-RType',
                                        tag: 'v0.0.0',
                                        draft: true,
                                        name: 'TEST'
                                    } */
                                    withCredentials([usernamePassword(credentialsId: '097d37a7-4a1b-4fc6-ba70-e13f043b70e8',
                                                                      usernameVariable: 'GITHUB_APP',
                                                                      passwordVariable: 'GITHUB_ACCESS_TOKEN')]) {
                                        bat '''
                                        curl -H "Content-Type: application/json" \
                                             -H "Accept: application/vnd.github.antiope-preview+json" \
                                             -H "authorization: Bearer ${GITHUB_ACCESS_TOKEN}" \
                                             -d '{ "name": "check_run", \
                                                   "head_sha": "'${GIT_COMMIT}'", \
                                                   "status": "in_progress", \
                                                   "external_id": "42", \
                                                   "started_at": "2020-03-05T11:14:52Z", \
                                                   "output": { "title": "Check run from Jenkins!", \
                                                               "summary": "This is a check run which has been generated from Jenkins as GitHub App", \
                                                               "text": "...and that is awesome"}}' https://api.github.com/repos/G-Epitech/DFMY-RType/check-runs
                                        '''
                                    }
                                }
                            }
                        }


                    }
                }
            }
        }

    }
}
