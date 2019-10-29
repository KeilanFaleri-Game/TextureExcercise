#include "GamePCH.h"
#include "Game.h"

Game::Game(fw::Framework* pFramework)
: GameCore( pFramework )
{
    m_VBO = 0;
    m_pShader = nullptr;
}

Game::~Game()
{
    delete m_pShader;
}

void Game::Init()
{
    // Turn on v-sync.
    wglSwapInterval( 1 );

    // Load a shader.
    m_pShader = new fw::ShaderProgram( "Data/Shaders/basic.vert", "Data/Shaders/basic.frag" );

    //Load Textures
    m_TextureID = fw::LoadTexture("Data/Textures/sexy.png");

    // Create a VBO and fill it with our vertex info.
    glGenBuffers( 1, &m_VBO );
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    VertexFormat attribs[] = { 
        VertexFormat( -0.5f, -0.5f, 0, 255, 0, 255, 0.0f, 0.0f ),
        VertexFormat(  0.0f,  0.5f, 0, 0, 255, 255, 0.5f, 1.0f),
        VertexFormat(  0.5f, -0.5f, 255, 0, 0, 255, 1.0f, 0.0f), };
    glBufferData( GL_ARRAY_BUFFER, sizeof(VertexFormat)*3, attribs, GL_STATIC_DRAW );
}

void Game::Update(float deltaTime)
{
    if( m_pFramework->IsKeyDown( VK_F1 ) )
    {
        // Turn on v-sync.
        wglSwapInterval( 1 );
    }
    if( m_pFramework->IsKeyDown( VK_F2 ) )
    {
        // Turn off v-sync.
        wglSwapInterval( 0 );
    }

    if( m_pFramework->IsKeyDown( 'W' ) )
    {
        fw::OutputMessage( "Up is pressed... and your framerate is approx: %0.0f fps\n", 1.0f/deltaTime );
    }
}

void Game::Draw()
{
    // Clear the screen.
    glClearColor( 0.0f, 0.0f, 0.4f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    // Setup our attributes.
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );

    GLint locPosition = glGetAttribLocation( m_pShader->GetProgram(), "a_Position" );
    if( locPosition != -1 )
    {
        glEnableVertexAttribArray( locPosition );
        glVertexAttribPointer( locPosition, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, x));
    }

    GLint locUV = glGetAttribLocation(m_pShader->GetProgram(), "a_UV");
    if (locUV != -1)
    {
        glEnableVertexAttribArray(locUV);
        glVertexAttribPointer(locUV, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, u));
    }

    GLint locColor = glGetAttribLocation( m_pShader->GetProgram(), "a_Color" );
    if( locColor != -1 )
    {
        glEnableVertexAttribArray( locColor );
        glVertexAttribPointer( locColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexFormat), (void*)offsetof(VertexFormat,r));
    }

    // Enable our shader.
    glUseProgram( m_pShader->GetProgram() );

    // Setup our uniforms.
    GLint locXOffset = glGetUniformLocation( m_pShader->GetProgram(), "u_XOffset" );
    glUniform1f( locXOffset, 0.0f );

    //SetUp Texture
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    GLint locTexture = glGetUniformLocation(m_pShader->GetProgram(), "u_Texture");
    glUniform1i(locTexture, 5);

    // Draw our shape.
    glDrawArrays( GL_TRIANGLES, 0, 3 );
}
