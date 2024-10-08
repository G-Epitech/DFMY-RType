BINARIES = ['client', 'server']
BINARIES_TARGETS = [
    'client': 'r-type_client',
    'server': 'r-type_server',
]
BINARIES_TESTS = [
    'client': 'r-type_client_tests',
    'server': 'r-type_server_tests'
]
LIBS = ['abra', 'zygarde']
LIBS_TARGETS = [
    'abra': [
        'target': 'abra',
        'type': 'shared'
    ],
    'zygarde': [
        'target': 'zygarde',
        'type': 'shared'
    ]
]
LIBS_TESTS = [
    'abra': 'abra_tests',
    'zygarde': 'zygarde_tests'
]
ARTIFACTS_FILES_EXTENSIONS = [
    'windows': ['exe', 'zip'],
    'unix': ['deb', 'tar.gz']
]

pipeline {
    agent any
    environment {
        RELEASE_ID = null
        VERSION = null
        MIRROR_URL = 'git@github.com:EpitechPromo2027/B-CPP-500-NAN-5-1-rtype-dragos.suceveanu.git'
    }
    stages {
        stage ('Check style') {
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
                        stage('Generate build files') {
                            steps {
                                script {
                                    bat 'cmake --preset=windows:release'
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
                                            fileExists("build/windows/release/libs/${lib}/${TARGET_LIB}.${TARGET_LIB_EXT}")
                                            bat "cmake --build build/windows/release --config release --target ${TARGET_TEST}"
                                            bat "xcopy build\\windows\\release\\libs\\${lib}\\*.dll build\\windows\\release\\libs\\${lib}\\tests /Y"
                                            bat "build\\windows\\release\\libs\\${lib}\\tests\\${TARGET_TEST}.exe"
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
                                            fileExists("build/windows/release/bin/${binary}/${TARGET_BINARY}.exe")
                                            bat "cmake --build build/windows/release --config release --target ${TARGET_TEST}"
                                            bat "xcopy build\\windows\\release\\${binary}\\*.dll build\\windows\\release\\${binary}\\tests /Y"
                                            bat "build\\windows\\release\\${binary}\\tests\\${TARGET_TEST}.exe"
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        stage ('Mirror') {
/*             when {
                branch 'main'
            } */
            steps {
                checkout scm
                script {
                    withCredentials([sshUserPrivateKey(credentialsId: 'G-EPIJENKINS_SSH_KEY', keyFileVariable: 'PRIVATE_KEY')]) {
                        sh 'export GIT_SSH_COMMAND="ssh -i $PRIVATE_KEY"'

                        if (sh(script: "git remote | grep mirror", returnStatus: true) == 0) {
                            sh "git remote remove mirror"
                        }

                        sh "git remote add mirror ${MIRROR_URL}"

                        sh "git checkout main"

                        sh "git push mirror"
                    }
                }
            }
        }

        stage ('Create Release') {
            when {
                buildingTag()
            }
            steps {
                script {
                    VERSION = sh(script: 'git describe --tags --abbrev=0', returnStdout: true).trim().substring(1)
                    echo "NEW VERSION IS $VERSION"
                }
                script {
                    withCredentials([usernamePassword(credentialsId: '097d37a7-4a1b-4fc6-ba70-e13f043b70e8',
                                                      usernameVariable: 'GITHUB_APP',
                                                      passwordVariable: 'GITHUB_ACCESS_TOKEN')]) {
                        def response = sh(script: """
                            curl -X GET -H "Authorization: Bearer \$GITHUB_ACCESS_TOKEN" \
                                 https://api.github.com/repos/G-Epitech/DFMY-RType/releases/tags/v$VERSION
                        """, returnStdout: true)

                        def jsonResponse = readJSON(text: response)
                        def releaseId = jsonResponse.id

                        if (releaseId) {
                            echo "Release ${releaseId} found, deleting it"
                            sh """
                                curl -X DELETE -H "Authorization: Bearer \$GITHUB_ACCESS_TOKEN" \
                                     https://api.github.com/repos/G-Epitech/DFMY-RType/releases/${releaseId}
                            """
                        } else {
                            echo "Release not found"
                        }
                    }
                }
                script {
                    withCredentials([usernamePassword(credentialsId: '097d37a7-4a1b-4fc6-ba70-e13f043b70e8',
                                                      usernameVariable: 'GITHUB_APP',
                                                      passwordVariable: 'GITHUB_ACCESS_TOKEN')]) {
                        def response = sh(script: """
                            curl -X POST -H "Content-Type: application/json" \
                                 -H "Authorization: Bearer \$GITHUB_ACCESS_TOKEN" \
                                 -d '{ "tag_name": "v$VERSION", \
                                       "name": "Release v$VERSION", \
                                       "body": "Description of the release.", \
                                       "draft": false, \
                                       "prerelease": false }' \
                                 https://api.github.com/repos/G-Epitech/DFMY-RType/releases
                        """, returnStdout: true)

                        def jsonResponse = readJSON(text: response)
                        def releaseId = jsonResponse.id

                        if (releaseId) {
                            echo "Release ${releaseId} created successfully"
                            RELEASE_ID = releaseId
                        } else {
                            error "Failed to create release"
                        }
                    }
                }
            }
        }

        stage ('Publish') {
            when {
                allOf {
                    buildingTag()
                    expression {
                        RELEASE_ID != null
                    }
                }
            }
            parallel {
                stage ('Unix Environment') {
                    agent {
                        dockerfile {
                            filename 'ci/unix.dockerfile'
                            reuseNode true
                        }
                    }

                    stages {
                        stage('Generate artifacts') {
                            steps {
                                script {
                                    for (binary in BINARIES) {
                                        def TARGET_BINARY = BINARIES_TARGETS[binary]

                                        stage ("${binary} artifacts") {
                                            sh "cmake --preset=unix:release:${binary}"
                                            sh "cmake --build build/unix/release --config release --target ${TARGET_BINARY}"
                                            sh "cd build/unix/release && cpack -C release"
                                        }
                                    }
                                }
                            }
                        }

                        stage('Upload artifacts') {
                            steps {
                                script {
                                    withCredentials([usernamePassword(credentialsId: '097d37a7-4a1b-4fc6-ba70-e13f043b70e8',
                                                                      usernameVariable: 'GITHUB_APP',
                                                                      passwordVariable: 'GITHUB_ACCESS_TOKEN')]) {
                                        for (binary in BINARIES) {
                                            extensions = ARTIFACTS_FILES_EXTENSIONS['unix']
                                            for (ext in extensions) {
                                                def filename = "R-Type-${binary}-${VERSION}.${ext}"
                                                sh """
                                                    curl -L \
                                                        -X POST \
                                                        -H "Accept: application/vnd.github+json" \
                                                        -H "Authorization: Bearer \$GITHUB_ACCESS_TOKEN" \
                                                        -H "Content-Type: application/octet-stream" \
                                                        "https://uploads.github.com/repos/G-Epitech/DFMY-RType/releases/${RELEASE_ID}/assets?name=${filename}" \
                                                        --data-binary "@build/unix/release/${filename}"
                                                """
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                stage ('Windows Environment') {
                    agent {
                        label 'windows'
                    }

                    stages {
                        stage('Generate artifacts') {
                            steps {
                                script {
                                    for (binary in BINARIES) {
                                        def TARGET_BINARY = BINARIES_TARGETS[binary]

                                        stage ("${binary} artifacts") {
                                            bat "cmake --preset=windows:release:${binary}"
                                            bat "cmake --build build/windows/release --config release --target ${TARGET_BINARY}"
                                            bat "cd build/windows/release && cpack -C release"
                                        }
                                    }
                                }
                            }
                        }

                        stage('Upload artifacts') {
                            steps {
                                script {
                                    withCredentials([usernamePassword(credentialsId: '097d37a7-4a1b-4fc6-ba70-e13f043b70e8',
                                                                      usernameVariable: 'GITHUB_APP',
                                                                      passwordVariable: 'GITHUB_ACCESS_TOKEN')]) {
                                        for (binary in BINARIES) {
                                            extensions = ARTIFACTS_FILES_EXTENSIONS['windows']
                                            for (ext in extensions) {
                                                def filename = "R-Type-${binary}-${VERSION}.${ext}"
                                                bat """
                                                    curl -L \
                                                        -X POST \
                                                        -H "Accept: application/vnd.github+json" \
                                                        -H "Authorization: Bearer %GITHUB_ACCESS_TOKEN%" \
                                                        -H "Content-Type: application/octet-stream" \
                                                        "https://uploads.github.com/repos/G-Epitech/DFMY-RType/releases/${RELEASE_ID}/assets?name=${filename}" \
                                                        --data-binary "@build/windows/release/${filename}"
                                                """
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
    }
}
