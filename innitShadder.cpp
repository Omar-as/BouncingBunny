namespace innitshader
{
    using namespace std;

    static char*
    readShaderSource(const char* filename)
    {
        auto file = fopen(filename, "r");

		if (file == NULL) 
        {
			cerr << "Failed to open " << filename << "." << endl;
			exit(EXIT_FAILURE);
		}

		// Determine file size
		fseek(file, 0, SEEK_END);
		auto file_size = ftell(file);

		auto code = new GLchar[file_size + 1];

		rewind(file);
		auto read_size = (long int) fread(code, sizeof(GLchar), file_size, file);

		if (read_size != file_size) 
        {
			cerr << "Failed to read " << filename << "." << endl;
			delete[] code;
			exit(EXIT_FAILURE);
		}

		// Terminate C-string
		code[file_size] = '\0';

		// Close file
		fclose(file);

        // cout << code << endl;

		return code;
    }


    // Create a GLSL program object from vertex and fragment shader files
    GLuint
    InitShader(const char* vShaderFile, const char* fShaderFile)
    {
        struct Shader 
        {
            const char*  filename;
            GLenum       type;
            GLchar*      source;
        }shaders[2] = { { vShaderFile, GL_VERTEX_SHADER  , NULL },
                        { fShaderFile, GL_FRAGMENT_SHADER, NULL } };

        GLuint program = glCreateProgram();
        
        for ( int i = 0; i < 2; ++i ) 
        {
            Shader& s = shaders[i];
            s.source = readShaderSource( s.filename );
            if ( shaders[i].source == NULL ) 
            {
                std::cerr << "Failed to read " << s.filename << std::endl;
                exit( EXIT_FAILURE );
            }

            GLuint shader = glCreateShader( s.type );
            glShaderSource( shader, 1, (const GLchar**) &s.source, NULL );
            glCompileShader( shader );

            GLint  compiled;
            glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
            if ( !compiled ) 
            {
                std::cerr << s.filename << " failed to compile:" << std::endl;
                GLint  logSize;
                glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logSize );
                char* logMsg = new char[logSize];
                glGetShaderInfoLog( shader, logSize, NULL, logMsg );
                std::cerr << logMsg << std::endl;
                delete [] logMsg;

                exit( EXIT_FAILURE );
            }

            delete [] s.source;

            glAttachShader( program, shader );
        }

        /* link  and error check */
        glLinkProgram(program);

        GLint  linked;
        glGetProgramiv( program, GL_LINK_STATUS, &linked );
        if ( !linked ) 
        {
            std::cerr << "Shader program failed to link" << std::endl;
            GLint  logSize;
            glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logSize);
            char* logMsg = new char[logSize];
            glGetProgramInfoLog( program, logSize, NULL, logMsg );
            std::cerr << logMsg << std::endl;
            delete [] logMsg;

            exit( EXIT_FAILURE );
        }

        /* use program object */
        glUseProgram(program);

        return program;
    }
}